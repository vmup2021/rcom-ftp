#include <stdio.h>
#include <stdlib.h>



#include "url.h"

int main(int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: download ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(1);
    }

    printf("I m inside the main function!");
    struct url u;
    parseUrl(argv[1], &u);

    return 0;
}
