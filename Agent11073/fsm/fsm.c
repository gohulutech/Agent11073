//
//  fsm.c
//  Agent11073
//
//  Created by Hugo Arevalo on 25/07/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fsm.h"
#include "../asn1/phd_types.h"
#include "../communication/tcp_client.h"

int sockfd;

systemState DisconnectedHandler(void) {
    return Disconnected;
}

systemState ConnectedUnassociatedHandler(void) {
    // Build Aarq APDU
    struct AARQ_apdu aarq_apdu;
    aarq_apdu.assoc_version = 0x80000000;
    aarq_apdu.data_proto_list.count = 1;
    aarq_apdu.data_proto_list.length = 42;
    
    struct DataProto dataProto;
    dataProto.data_proto_id = 0x5079;
    dataProto.data_proto_info.length = 38;
    intu8 dataProtoInfoValue[] = { 0x80, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x08, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x40, 0x00, 0x00, 0x81, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00};
    dataProto.data_proto_info.value = dataProtoInfoValue;
    
    aarq_apdu.data_proto_list.value = &dataProto;
    
    // Send APDU over TCP
    unsigned char *buffer = (unsigned char*)malloc(54);
    buffer[0] = 0xE2;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    buffer[3] = 0x32;
    buffer[4] = (aarq_apdu.assoc_version >> 24) & 0xFF;
    buffer[5] = (aarq_apdu.assoc_version >> 16) & 0xFF;
    buffer[6] = (aarq_apdu.assoc_version >> 8) & 0xFF;
    buffer[7] = aarq_apdu.assoc_version & 0xFF;
    buffer[8] = (aarq_apdu.data_proto_list.count >> 8) & 0xFF;
    buffer[9] = aarq_apdu.data_proto_list.count & 0xFF;
    buffer[10] = (aarq_apdu.data_proto_list.length >> 8) & 0xFF;
    buffer[11] = aarq_apdu.data_proto_list.length & 0xFF;
    buffer[12] = (dataProto.data_proto_id >> 8) & 0xFF;
    buffer[13] = dataProto.data_proto_id & 0xFF;
    buffer[14] = (dataProto.data_proto_info.length >> 8) & 0xFF;
    buffer[15] = dataProto.data_proto_info.length & 0xFF;
    
    for (int i = 0; i < dataProto.data_proto_info.length; i++) {
        buffer[i + 16] = dataProtoInfoValue[i];
    }
        
    sendBytes(sockfd, buffer);
    
    
    free(buffer);
    
    return ConnectedUnassociated;
}

systemState ConnectedAssociatingHandler(void) {
    return ConnectedAssociating;
}

systemState ConnectedAssociatedConfiguringSendingConfigHandler(void) {
    return ConnectedAssociatedConfiguringSendingConfig;
}

systemState ConnectedAssociatedConfiguringWaitingApprovalHandler(void) {
    return ConnectedAssociatedConfiguringWaitingApproval;
}

systemState ConnectedAssociatedOperatingHandler(void) {
    return ConnectedAssociatedOperating;
}

systemState ConnectedDisassociatingHandler(void) {
    return ConnectedDisassociating;
}

StateMachineStruct asStateMachine [] = {
    {Disconnected, TransportConnectIndication, ConnectedUnassociatedHandler},
    {ConnectedUnassociated, TransportDisconnectIndication, DisconnectedHandler},
    {ConnectedUnassociated, AssocReq, ConnectedAssociatingHandler}, // Tx aarq
    {ConnectedUnassociated, AssocAbort, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedUnassociated, RxAssocReq, ConnectedUnassociatedHandler}, // Tx aare (rejected-permanent)
    {ConnectedUnassociated, RxAssocRspAccepted, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociating, RxAssocRspAcceptedUnknownConfig, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedUnassociated, RxAssocRspRejected, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedUnassociated, RxAssocRelReq, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedUnassociated, RxAssocRelRsp, ConnectedUnassociatedHandler},
    {ConnectedUnassociated, RxAssocAbort, ConnectedUnassociatedHandler},
    {ConnectedAssociating, TransportDisconnectIndication, DisconnectedHandler},
    {ConnectedAssociating, AssocRelReq, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociating, AssocAbort, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociating, RxAssocReq, ConnectedUnassociatedHandler}, // Tx aare (rejected-permanent)
    {ConnectedAssociating, RxAssocRspAccepted, ConnectedAssociatedOperatingHandler},
    {ConnectedAssociating, RxAssocRspAcceptedUnknownConfig, ConnectedAssociatedConfiguringSendingConfigHandler},
    {ConnectedAssociating, RxAssocRspRejected, ConnectedUnassociatedHandler},
    {ConnectedAssociating, RxAssocRelReq, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociating, RxAssocRelRsp, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociating, RxAssocAbort, ConnectedUnassociatedHandler},
    {ConnectedAssociatedConfiguringSendingConfig, TransportDisconnectIndication, DisconnectedHandler},
    {ConnectedAssociatedConfiguringSendingConfig, AssocRelReq, ConnectedDisassociatingHandler}, // Tx rlrq
    {ConnectedAssociatedConfiguringSendingConfig, AssocAbort, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringSendingConfig, RxAssocReq, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringSendingConfig, RxAssocRspAccepted, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringSendingConfig, RxAssocRspAcceptedUnknownConfig, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringSendingConfig, RxAssocRspRejected, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringSendingConfig, RxAssocRelReq, ConnectedUnassociatedHandler}, // Tx rlre(normal)
    {ConnectedAssociatedConfiguringSendingConfig, RxAssocRelRsp, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringSendingConfig, RxAssocAbort, ConnectedUnassociatedHandler},
    {ConnectedAssociatedConfiguringWaitingApproval, TransportDisconnectIndication, DisconnectedHandler},
    {ConnectedAssociatedConfiguringWaitingApproval, AssocRelReq, ConnectedDisassociatingHandler}, // Tx rlrq
    {ConnectedAssociatedConfiguringWaitingApproval, AssocAbort, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringWaitingApproval, RxAssocReq, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringWaitingApproval, RxAssocRspAccepted, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringWaitingApproval, RxAssocRspAcceptedUnknownConfig, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringWaitingApproval, RxAssocRspRejected, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringWaitingApproval, RxAssocRelReq, ConnectedUnassociatedHandler}, // Tx rlre(normal)
    {ConnectedAssociatedConfiguringWaitingApproval, RxAssocRelRsp, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedConfiguringWaitingApproval, RxAssocAbort, ConnectedUnassociatedHandler},
    {ConnectedAssociatedOperating, TransportDisconnectIndication, DisconnectedHandler},
    {ConnectedAssociatedOperating, AssocRelReq, ConnectedDisassociatingHandler}, // Tx rlrq
    {ConnectedAssociatedOperating, AssocAbort, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedOperating, RxAssocReq, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedOperating, RxAssocRspAccepted, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedOperating, RxAssocRspAcceptedUnknownConfig, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedOperating, RxAssocRspRejected, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedAssociatedOperating, RxAssocRelReq, ConnectedUnassociatedHandler}, // Tx rlre(normal)
    {ConnectedAssociatedOperating, RxAssocRelRsp, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedDisassociating, RxAssocAbort, ConnectedUnassociatedHandler},
    {ConnectedDisassociating, TransportDisconnectIndication, DisconnectedHandler},
    {ConnectedDisassociating, AssocRelReq, ConnectedDisassociatingHandler}, // Tx rlrq
    {ConnectedDisassociating, AssocAbort, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedDisassociating, RxAssocReq, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedDisassociating, RxAssocRspAccepted, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedDisassociating, RxAssocRspAcceptedUnknownConfig, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedDisassociating, RxAssocRspRejected, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedDisassociating, RxAssocRelReq, ConnectedUnassociatedHandler}, // Tx rlre(normal)
    {ConnectedDisassociating, RxAssocRelRsp, ConnectedUnassociatedHandler}, // Tx abrt
    {ConnectedDisassociating, RxAssocAbort, ConnectedUnassociatedHandler},
};

systemState getNextState(systemEvent event, systemState nextState)
{
    if ((nextState < lastState) && (event < lastEvent) && (asStateMachine[nextState].stateMachineEvent == event) && (asStateMachine[nextState].stateMachineEventHandler != NULL))
    {
        return (*asStateMachine[nextState].stateMachineEventHandler)();
    }
    return Disconnected;
}

int initializeFsm(void) {
    sockfd = initializeTcpClient();
    return sockfd;
}
