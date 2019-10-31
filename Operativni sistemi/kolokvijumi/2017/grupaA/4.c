#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <string.h>

#define MAX_SIZE (256)

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 3, "bad arg count");
    check_error(!strcmp(argv[1], "-r") && !strcmp(argv[1], "-w") && !strcmp(argv[1], "-a"), "bad argv[1]");

    int open_file;
    int bufferRead = 0;
    char* buffer = malloc(MAX_SIZE*sizeof(char));
    check_error(buffer == NULL, "bad buffer malloc");

    if(!strcmp(argv[1], "-r")){
        check_error((open_file = open(argv[2], O_RDONLY)) == -1, "open (r) failure");
        while((bufferRead = read(open_file, buffer, MAX_SIZE)) > 0){
            check_error(write(STDOUT_FILENO, buffer, bufferRead) != bufferRead, "writing (r) failure");
        }
        check_error(bufferRead == -1, "reading failure");
    }
    else if(!strcmp(argv[1], "-w")){
        check_error((open_file = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT)) == -1, "open (w) failure");
        while((bufferRead = read(STDIN_FILENO, buffer, MAX_SIZE)) > 0){
            check_error(write(open_file, buffer, bufferRead) == -1, "writing (w) failure");
        }
    }
    else{
        check_error((open_file = open(argv[2], O_RDWR | O_CREAT | O_APPEND)) == -1, "open (a) failure");
        while((bufferRead = read(STDIN_FILENO, buffer, MAX_SIZE)) > 0){
            check_error(write(open_file, buffer, bufferRead) == -1, "writing (a) failure");
        }
    }

    free(buffer);
    close(open_file);
    exit(EXIT_SUCCESS);
}