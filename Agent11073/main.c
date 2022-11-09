//
//  main.c
//  Agent11073
//
//  Created by Hugo Arevalo on 17/07/22.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "communication/tcp_client.h"
#include "fsm/fsm.h"
#include "fsm/event.h"
#define MAX 80
#define SA struct sockaddr

int main(int argc, const char * argv[]) {
    char buff[MAX];
    int sockfd;
    printf("Application started.\n");
    sockfd = initializeFsm();
    systemState nextState = Disconnected;
    systemEvent event = TransportConnectIndication;
    systemState currentState;
        
    while(1)
    {
        currentState = getNextState(event, nextState);
        readBytes(sockfd);
        event = ReadEvent();
    }
    
    return 0;
}
