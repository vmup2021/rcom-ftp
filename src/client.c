#include "../include/client.h"

int openSocket(char *ip, int port, int *socketFd) {
    struct sockaddr_in serverAddr;

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(port);

    if ((*socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Error opening the socket");
        return -1;
    }

    if (connect(*socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "Error connecting to the server");
        return -1;
    }

    return 0;
}

int login(int socketFd, char *username, char *password) {
    int statusCodes[2] = {};

    if (sendCommand(socketFd, USER, 1, username) < 0) {
        fprintf(stderr, "Failed to send the USER command.\n");
        return -1;
    }
    char response[4112] = {0};
    statusCodes[0] = CMD_USERNAME_OK;
    checkStatusCode(socketFd, statusCodes, 1, response);

    if (sendCommand(socketFd, PASS, 1, password) < 0) {
        fprintf(stderr, "Failed to send the PASS command.\n");
        return -1;
    }
    statusCodes[0] = CMD_LOGIN_SUCCESS;
    checkStatusCode(socketFd, statusCodes, 1, response);

    return 0;
}

int enterPassiveMode(int socketFd, char *ip, int *port) {
    int statusCodes[1] = {};

    if (sendCommand(socketFd, PASV, 0, NULL) < 0) {
        fprintf(stderr, "Failed to send the PASV command.\n");
        return -1;
    }
    char response[4112] = {0};
    statusCodes[0] = CMD_PASSIVE_MODE;
    checkStatusCode(socketFd, statusCodes, 1, response);

    int ip1, ip2, ip3, ip4;
    int p1, p2;

    // Passive mode returns the IP and port in the format (ip1,ip2,ip3,ip4,p1,p2)
    // We need to extract the IP and port from this string
    sscanf(response, "%*[^(](%d,%d,%d,%d,%d,%d)", &ip1, &ip2, &ip3, &ip4, &p1, &p2);

    sprintf(ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
    // The port is two bytes, so we need to multiply the first byte by 256 and add the second byte
    // to get the decimal value
    *port = p1 * 256 + p2;

    return 0;
}

int sendCommand(int socketFd, char *command, int hasArgs, char *args) {
    char cmd[128];

    strcpy(cmd, command);

    if (hasArgs) {
        strcat(cmd, " ");
        strcat(cmd, args);
    }
    // printf("%s\n", args);

    strcat(cmd, CRLF);

    size_t result = write(socketFd, cmd, strlen(cmd));

    if (result != strlen(cmd)) {
        fprintf(stderr, "Error writing command to the socket\n");
        return -1;
    }

    printf("App > %s\n", cmd);

    return 0;
}

int readResponse(int socketFd, int *statusCode, char* response) {
    FILE *socket = fdopen(socketFd, "r");

    // char *buffer = malloc(1028);
    char *buffer;
    size_t bytesRead = 0;
    int totalBytes = 0;

    // char *response = calloc(1, 4112);

    while (getline(&buffer, &bytesRead, socket) > 0) {
        strncat(response, buffer, bytesRead - 1);
        totalBytes += bytesRead;

        if (buffer[3] == ' ') {
            sscanf(buffer, "%d", statusCode);
            break;
        }
    }
    // printf("App < %s\n", response);

    // printf("The status code is %d\n", *statusCode);
    // printf("The total number of bytes is: %d\n", totalBytes);

    return totalBytes;
}

int checkStatusCode(int socketFd, int validStatusCodes[], int length, char* response) {
    static int statusCode = 0;

    if (readResponse(socketFd, &statusCode, response) < 0) {
        fprintf(stderr, "Failed reading the response in checkStatusCode function.\n");
        return -1;
    }

    int valid = 0;

    for (int i = 0; i < length; i++) {
        if (statusCode == validStatusCodes[i]) {
            valid = 1;
            break;
        }
    }

    printf("App STATUS CODE GOT: %d\n", statusCode);

    if (valid == 0) {
        fprintf(stderr, "Incorrect status code returned!\n");
        return -1;
    }

    return 0;
}

int requestServerFile(int socketFd, char *file) {
	int statusCodes[1] = {};

	if (sendCommand(socketFd, RETR, 1, file) < 0) {
		fprintf(stderr, "Failed to send the RETR command.\n");
		return -1;
	}
    printf("Sent the RETR command\n");
	char response[4112] = {0};
	statusCodes[0] = CMD_RETR_READY;
	return checkStatusCode(socketFd, statusCodes, 1, response);
}

int transferServerFile(int socketFd, int socketFdTransfer, char *file) {
    FILE *fileFd = fopen(file, "w");

    if (fileFd == NULL) {
        fprintf(stderr, "Failed to open the file.\n");
        return -1;
    }

    char buffer[1024];
    int bytesRead = 0;
    int totalBytes = 0;

    while ((bytesRead = read(socketFdTransfer, buffer, 1024)) > 0) {
        fwrite(buffer, 1, bytesRead, fileFd);
        totalBytes += bytesRead;
        printf("\rBytes read: %d", totalBytes); // Use \r to move the cursor back to the start of the line
        fflush(stdout); // Use fflush to immediately update the output
    }
    printf("\n");

    fclose(fileFd);

    int statusCodes[1] = {CMD_TRANSFER_COMPLETE};
    char response[4112] = {0};
    return checkStatusCode(socketFd, statusCodes, 1, response);
}

int endConnection(int fd) {
    if (sendCommand(fd, QUIT, 0, NULL) < 0) {
        fprintf(stderr, "Failed to send the QUIT command, closing fd either way.\n");
        close(fd);
        return -1;
    }

    int statusCodes[1] = {CMD_QUIT_OK};
    char response[4112] = {0};
    int correctStatus = checkStatusCode(fd, statusCodes, 1, response);

    close(fd);
    return correctStatus;
}
