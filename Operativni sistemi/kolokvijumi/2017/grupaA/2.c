#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <pwd.h>
#include <grp.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 2, "bar arg count");

    struct stat fileInfo;

    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");

    struct passwd *pwnam;

    check_error((pwnam = getpwuid(fileInfo.st_uid)) == NULL, "getpwnam failure");

    struct group *grnam;

    check_error((grnam = getgrgid(fileInfo.st_gid)) == NULL, "bad getgrnam");

    fprintf(stdout, "%s %s\n", pwnam->pw_name, grnam->gr_name);

    exit(EXIT_SUCCESS);
}