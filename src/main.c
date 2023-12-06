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
    int fd = openSocket(u.ip, 21);
    int _[1] = {CMD_SOCKET_READY};
    checkStatusCode(fd, _, 1);
   
    login(fd, u.user, u.pass);

    // Sending the HELP command just to check
    sendCommand(fd,HELP,0, NULL);

    int c[1] = {CMD_HELP_OK};

    checkStatusCode(fd, c, 1);

    return 0;
}
