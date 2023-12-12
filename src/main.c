#include "../include/url.h"
#include "../include/client.h"
#include "../include/constants.h"

// Need to connect to the VPN
//./my_program ftp://rcom:rcom@netlab1.fe.up.pt/path

int main(int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: download ftp://[user:<password]@<host>/<url-path>\n");
        exit(1);
    }

    // Parse the URL
    struct url u;
    parseUrl(argv[1], &u);

    // Open the socket and check return value
    int fd = 0;
    // Here port is hardcoded on 21, but wtv
    if(openSocket(u.ip, 21, &fd) != 0) {
        printf("Error opening the socket");
        return 1;
    }
    int _[1] = {CMD_SOCKET_READY};
    char response[4112];
    checkStatusCode(fd, _, 1, response);
   
    if(login(fd, u.user, u.pass) != 0) {
        printf("Error in login function");
        return 1;
    }

    // // Sending the HELP command just to check
    // sendCommand(fd,HELP,0, NULL);

    // int c[1] = {CMD_HELP_OK};

    // checkStatusCode(fd, c, 1);

    // Enter passive mode
    if(enterPassiveMode(fd, u.ip, &u.transferPort) != 0) {
        printf("Error in enterPassiveMode");
        return 1;
    }
    printf("Got this from passive mode: %s:%d\n", u.ip, u.transferPort);

    int fd_transfer = 0;
    if(openSocket(u.ip, u.transferPort, &fd_transfer) != 0) {
        printf("Error opening the socket");
        return 1;
    }
    printf("Opened socket to transfer file\n");
    
    printf("Requesting server file %s\n", u.path);
    if (requestServerFile(fd, u.path) != 0) {
        printf("Error requesting server resource");
        return 1;
    }
    printf("Requested server file %s\n", u.filename);

    if (transferServerFile(fd, fd_transfer, u.filename) != 0) {
        printf("Error transfering server resource");
        return 1;
    }
    printf("Transfered server file %s\n", u.filename);

    if (endConnection(fd) != 0) {
        printf("Error ending connection, still closed the fd tho :)");
        return 1;
    }
    printf("Ended connection\n");

    return 0;
}
