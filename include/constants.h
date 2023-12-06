#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// FTP COMMANDS
#define USER "USER"
#define PASS "PASS"
#define PASV "PASV"
#define RETR "RETR"
#define QUIT "QUIT"
#define HELP "HELP"

// This string must be sent after every command to indicate the end of it
#define CRLF "\r\n" 

// STATUS CODE RETURNED BY THE FTP SERVER
#define CMD_SOCKET_READY        220         // Socket Ready
#define CMD_LOGIN_SUCCESS       230         // Login succsessful
#define CMD_USERNAME_OK         331         // Username successful
#define CMD_NOT_LOGGED_IN       530         // Error in login
#define CMD_PASV_MODE           227         // Passive mode entered
#define CMD_RETR_READY          150         // File is ready to be downloaded
#define CMD_TRANSFER_COMPLETE   226         // Transfer complete
#define CMD_HELP_OK 		214         // Help command sucessful
#endif
