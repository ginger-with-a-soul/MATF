#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define check_error(expr, userMsg)\
    do{\
        if(expr){\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

int main(int argc, char** argv){

    check_error(argc != 2, "bad argc count");

    struct stat fileInfo;

    check_error(stat(argv[1], &fileInfo) == -1, "stat failure");

    char* string = calloc(11, sizeof(char));
    check_error(string == NULL, "bad string malloc");



    if(S_ISREG(fileInfo.st_mode)){
        string[0] = '-';
    }
    else if(S_ISDIR(fileInfo.st_mode)){
        string[0] = 'd';
    }
    else if(S_ISCHR(fileInfo.st_mode)){
        string[0] = 'c';
    }
    else if(S_ISBLK(fileInfo.st_mode)){
        string[0] = 'b';
    }
    else if(S_ISFIFO(fileInfo.st_mode)){
        string[0] = 'p';
    }
    else if(S_ISLNK(fileInfo.st_mode)){
        string[0] = 'l';
    }
    else{
        string[0] = 's';
    }

    if(fileInfo.st_mode & S_IRUSR){
        string[1] = 'r';
    }
    else{
        string[1] = '-';
    }
    if(fileInfo.st_mode & S_IWUSR){
        string[2] = 'w';
    }
    else{
        string[2] = '-';
    }
    if(fileInfo.st_mode & S_IXUSR){
        string[3] = 'x';
    }
    else{
        string[3] = '-';
    }
    if(fileInfo.st_mode & S_IRGRP){
        string[4] = 'r';
    }
    else{
        string[4] = '-';
    }
    if(fileInfo.st_mode & S_IWGRP){
        string[5] = 'w';
    }
    else{
        string[5] = '-';
    }
    if(fileInfo.st_mode & S_IXGRP){
        string[6] = 'x';
    }
    else{
        string[6] = '-';
    }
    if(fileInfo.st_mode & S_IROTH){
        string[7] = 'r';
    }
    else{
        string[7] = '-';
    }
    if(fileInfo.st_mode & S_IWOTH){
        string[8] = 'w';
    }
    else{
        string[8] = '-';
    }
    if(fileInfo.st_mode & S_IXOTH){
        string[9] = 'x';
    }
    else{
        string[9] = '-';
    }

    fprintf(stdout, "%s\n", string);

    free(string);

    exit(EXIT_SUCCESS);
}