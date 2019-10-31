#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE (256   )

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 3, "bad arg count");
    char* src, *dest;
    check_error((src = realpath(argv[1], NULL)) == NULL, "src doesn't exist");
    check_error((dest = realpath(argv[2], NULL)) == NULL, "dest doesn't exist");
    check_error(!strcmp(src, dest), "src and dest can't be the same");
    free(src);
    free(dest);

    int writeDest;
    FILE* readSrc;
    check_error((readSrc = fopen(argv[1], "r")) == NULL, "open 1 failure");
    check_error((writeDest = open(argv[2], O_WRONLY)) == -1, "open 2 failure");

    int offset;
    char* word = calloc(sizeof(char), MAX_SIZE);
    check_error(word == NULL, "calloc failure");

    while(fscanf(readSrc, "%i %s", &offset, word) == 2){
        check_error(lseek(writeDest, offset, SEEK_SET) == -1, "lseek failure");
        check_error(write(writeDest, word, strlen(word)) == -1, "write failure");

    }

    free(word);
    fclose(readSrc);
    close(writeDest);
    exit(EXIT_SUCCESS);
}