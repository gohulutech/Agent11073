//
//  fsm.c
//  Agent11073
//
//  Created by Hugo Arevalo on 25/07/22.
//

#include "fsm.h"

systemState DisconnectedHandler(void) {
    return Disconnected;
}

systemState ConnectedUnassociatedHandler(void) {
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
