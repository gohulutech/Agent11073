//
//  fsm.h
//  Agent11073
//
//  Created by Hugo Arevalo on 25/07/22.
//

#ifndef fsm_h
#define fsm_h

#include <stdio.h>



typedef enum {
    Disconnected,
    ConnectedDisassociating,
    ConnectedUnassociated,
    ConnectedAssociating,
    ConnectedAssociated,
    ConnectedAssociatedOperating,
    ConnectedAssociatedConfiguringSendingConfig,
    ConnectedAssociatedConfiguringWaitingApproval,
    lastState
} systemState;

typedef enum {
    TransportConnectIndication,
    TransportDisconnectIndication,
    AssocAbort,
    AssocRelReq,
    AssocReq,
    RxAssocAbort,
    RxAssocRelReq,
    RxAssocRelRsp,
    RxAssocReq,
    RxAssocRspAccepted,
    RxAssocRspAcceptedUnknownConfig,
    RxAssocRspRejected,
    TxAssocAbort,
    TxAssocRelRsp,
    TxAssocReq,
    TxAssocRsp,
    RxConfigEventReportRsp,
    TxConfigEventReportReq,
    lastEvent
} systemEvent;

typedef systemState (*eventHandler)(void);

typedef struct {
    systemState stateMachine;
    systemEvent stateMachineEvent;
    eventHandler stateMachineEventHandler;
} StateMachineStruct;

systemState getNextState(systemEvent event, systemState nextState);

int initializeFsm(void);

#endif /* fsm_h */
