#include "../include/url.h"

int parseUrl(char *url, struct url* u){
    char *_ = strtok(url, "/");
    char *userPassHost = strtok(NULL, "/");
    char *path = strtok(NULL, ""); // This line

    if(_ == NULL){
        fprintf(stderr, "Invalid URL, must specify the protocol.\n");
    }
    if(userPassHost == NULL){
        fprintf(stderr, "Invalid URL, need to set user, password and host to connect to.\n");
    }
    if(path == NULL){
        fprintf(stderr, "Invalid URL, must specify the file path desired.\n");
    }

    // Case user is setted
    if(hasUser(userPassHost)){
        char *userPass = strtok(userPassHost, "@");
        char *host = strtok(NULL , "@");

        char *user = strtok(userPass, ":");
        char *pass = strtok(NULL, ":");

        // Pass the user to the struct url
        strcpy(u->user, user);

        // Pass the password to the struct url
        if(pass == NULL){
            fprintf(stderr, "The user must be followed by a password!\n");
            exit(1);
        }
        else { 
            strcpy(u->pass, pass);
        }

        // Pass the host to the struct url
        strcpy(u->host, host);
    }
    else {
        strcpy(u->user, "anonymous");
            strcpy(u->pass, "pass");
            strcpy(u->host, userPassHost);
        // In the case, as only the host is passed, the userPassHost is the host 
    }

    
    // Pass the filename and the path to the struct url and check them...
    char *filename = getFilename(path);
    strcpy(u->filename, filename);
    strcpy(u->path, path);
    if (!strcmp(u->host, "") || !strcmp(u->path, "")) {
            fprintf(stderr, "Invalid URL!\n");
            return -1;
        }


        struct hostent * h;

        if ((h = gethostbyname(u->host)) == NULL) {  
            perror("gethostbyname");
            return -1;
        }

        strcpy(u->hostname, h->h_name);

        char * ip = inet_ntoa(*((struct in_addr *)h->h_addr));
        strcpy(u->ip, ip);

    // printf("User %s\n", u->user);
    // printf("Pass %s\n", u->pass);
    // printf("Host %s\n", u->host);
    // printf("Path %s\n", u->path);
    // printf("Filename %s\n", u->filename);
    // printf("Hostname %s\n", u->hostname);
    // printf("IP address %s\n", u->ip);

    return 0;
}

int hasUser(char *userPassHost){
    return strchr(userPassHost, '@') != NULL ? 1 : 0;
}

char *getFilename(char *path) {
    const char* lastSlash = strrchr(path, '/');

    if (lastSlash != NULL) {
        // If the last component is not empty, return it
        if (*(lastSlash + 1) != '\0') {
            return strdup(lastSlash + 1);
        }
    }

   return path;
}
