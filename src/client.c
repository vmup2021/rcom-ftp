#include "../include/client.h"

int openSocket(char *ip, int port){
	int socketFd;
	struct sockaddr_in server_addr;

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);

	if( (socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
		fprintf(stderr, "Error opening the socket");
		return -1;
	}

	// Connect to the ip passed in the parameter
	if(connect(socketFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		fprintf(stderr, "Error connecting to the ip");
		return -1;
	}
	
	return socketFd;
}


int login(int socketFd, char *user, char *pass){
	/* Array to pass status code's to the checkStatusCodes function.
	 * Has a fixed size of 2, thinking that would be the bigger number 
	 * of status code that I would check(if wrong, just increase).
	 * Always control the length of it in the checkStatusCode func*/
	int temp[2] = {};
	
	// Send the USER command and check status code
	if(sendCommand(socketFd, USER, 1, user) < 0){
		fprintf(stderr, "Failed to send the USER command.\n");
		return -1;
	}
	temp[0] = CMD_USERNAME_OK;
	checkStatusCode(socketFd, temp, 1);

	// Send the PASS comm...
	if(sendCommand(socketFd, PASS, 1, pass) < 0){
		fprintf(stderr, "Failed to send the PASS command.\n");
		return -1;
	}
	temp[0] = CMD_LOGIN_SUCCESS; 
	checkStatusCode(socketFd, temp, 1);

	return 0;
}


int sendCommand(int socketFd, char *command, int hasArgs, char *args){
	char cmd[128];

	// Mount up the command
	strcpy(cmd, command);
	
	if(hasArgs) {
		strcat(cmd, " ");
		strcat(cmd, args);
	}

	// Need to send this string to end the command
	strcat(cmd, CRLF);

	size_t result = write(socketFd, cmd, strlen(cmd));

	// Now write the command to the FD
	if(result != strlen(cmd)){
		fprintf(stderr, "Error writing command to the FD\n");
		return -1;
	}

	printf("> %s\n", cmd);

	return 0;
}

// Prints the reponse from the server and store the status code(what matters)
int readResponse(int socketFd, int *code){
	FILE *socket = fdopen(socketFd, "r");

	char *buffer = malloc(1028);
	size_t bytesRead = 0;
	int totalBytes = 0;

	char *response = calloc(1, 4112);

	// Reads response line by line. Stops when the line is the reponse status code
	while(getline(&buffer, &bytesRead, socket) > 0){
		strncat(response, buffer, bytesRead-1);
		totalBytes += bytesRead;

		if(buffer[3] == ' '){
			sscanf(buffer, "%d", code);
			break;
		}
	}
	printf("< %s\n",response);

	free(buffer);
	free(response);
	printf("The code is %d\n", *code);
	printf("The total number of bytes is:%d\n", totalBytes);

	return totalBytes;
}


// Pass a list of possible status codes to be returned after a sendCommand
int checkStatusCode(int socketFd, int statusCodesPossible[], int length){
	static int code = 0;

	if(readResponse(socketFd, &code) < 0 ){
		fprintf(stderr, "Failed reading the response in checkStatusCode function.\n");
		return -1;
	}

	int valid = 0;
	
	for(int i = 0; i <length; i++)
		if(code == statusCodesPossible[i]) valid = 1;
	

	printf("STATUS CODE GOT: %d\n", code);

	if(valid == 0){
		fprintf(stderr, "Incorrect status code returned!\n");
		return -1;
	}

	return 0;
}

