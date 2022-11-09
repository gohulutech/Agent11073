//
//  tcp_client.h
//  Agent11073
//
//  Created by Hugo Arevalo on 25/10/22.
//

#ifndef tcp_client_h
#define tcp_client_h

#include <stdio.h>
#include <stdbool.h>
#include "../asn1/phd_types.h"

void func(int sockfd);
void checkConditionOrExit(bool condition, const char* successMessage, char* errorMessage);
int initializeTcpClient(void);
void sendBytes(int sockfd, unsigned char* buffer);
void readBytes(int sockfd);

#endif /* tcp_client_h */
