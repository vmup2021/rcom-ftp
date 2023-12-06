#include <netdb.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h> // For close
#include <arpa/inet.h>
#define h_addr h_addr_list[0] /* for backward compatibility */

struct url {
	char host[128];
	char hostname[128];
	char ip[128];
	char user[128];
	char pass[128];
	char path[256];
	char filename[128];
};


int parseUrl(char *url, struct url *u);

int getIPAddress(struct url *u);

char *getFilename(char *path);

int hasUser(char *userPassHost);
