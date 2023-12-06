#ifndef _CLIENT_H_
#define _CLIENT_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h> 
#include <netdb.h> 
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

#include "constants.h"

int openSocket(char *ip, int port);

int login(int socketFd, char *user, char *pass);

int enterPassiveMode(int socketFd, char *ip, int *port);

int sendCommand(int socketFd, char *command, int hasArgs, char *args);

int checkStatusCode(int socketFd, int *validStatusCodes, int length, char* response);

int readResponse(int socketFd, int *code, char* response);

#endif
