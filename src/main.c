#include "../include/url.h"
#include "../include/client.h"
#include "../include/constants.h"

int main(int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(1);
    }

    struct url u;
    parseUrl(argv[1], &u);

    // Opening the socket and checking the return value
    int fd = openSocket(u.ip, 21);

    int a[1] = {CMD_SOCKET_READY};

    checkStatusCode(fd, a, 1);
   
    // Sending the USER command and checking the return value
    sendCommand(fd, USER, 1, u.user);  

    int valids[1] = {CMD_USERNAME_OK};
    
    checkStatusCode(fd, valids, 1);

    // Sending the PASS command and checking the return value
    sendCommand(fd, PASS, 1, u.pass);

    int b[1] = {CMD_LOGIN_SUCCESS};

    checkStatusCode(fd, b, 1);

    // Sending the HELP command just to check
    sendCommand(fd,HELP,0, NULL);

    int c[1] = {CMD_HELP_OK};

    checkStatusCode(fd, c, 1);

    return 0;
}
