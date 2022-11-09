//
//  tcp_client.c
//  Agent11073
//
//  Created by Hugo Arevalo on 25/10/22.
//
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#define MAX 80
#define PORT 6024
#define SA struct sockaddr

#include "tcp_client.h"
#include "../asn1/phd_types.h"

void func(int sockfd)
{
    char buff[MAX];
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
}

void checkConditionOrExit(bool condition, const char* successMessage, char* errorMessage) {
    if (!condition) {
        printf("%s", errorMessage);
        exit(0);
    }
    
    printf("%s", successMessage);
}

int initializeTcpClient(void) {
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    checkConditionOrExit(sockfd != -1, "Socket successfully created..\n", "socket creation failed...\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.64.3");
    servaddr.sin_port = htons(PORT);

    checkConditionOrExit(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) == 0
                         , "connected to the server..\n"
                         , "connection with the server failed...\n");
    
    return sockfd;
}

void sendBytes(int sockfd, unsigned char* buffer) {
    printf("Sent bytes:\n");
    for(int i = 0; i < MAX; i++)
        printf("%02X ", buffer[i]);
    
    printf("\n");
    
    write(sockfd, buffer, 54);
}

void readBytes(int sockfd) {
    char buff[MAX];
    read(sockfd, buff, sizeof(buff));
    
    printf("Received bytes:\n");
    
    for(int i = 0; i < MAX; i++)
        printf("%02X ", buff[i]);
    
    printf("\n");
}
