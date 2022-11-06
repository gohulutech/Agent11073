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
    systemState nextState = Disconnected;
    systemEvent event;
    systemState currentState;
    int sockfd;
    char buff[MAX];
    
    sockfd = initializeTcpClient();
    func(sockfd);
    close(sockfd);
    
    int n;
    
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        
        while ((buff[n++] = getchar()) != '\n')
            ;
        
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
     
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
    
    /*while(1)
    {
        event = ReadEvent();
        currentState = getNextState(event, nextState);
    }*/
    
    return 0;
}


