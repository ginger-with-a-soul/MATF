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

    check_error(argc != 3, "bar arg count");

    char *srcPath, *destPath;
    check_error((srcPath = realpath(argv[1], NULL)) == NULL, "no src file");
    check_error((destPath = realpath(argv[1], NULL)) == NULL, "no dest file");

    free(srcPath);
    free(destPath);

    int src, dest;
    check_error((src = open(argv[1], O_RDONLY)) == -1, "src open failure");
    check_error((dest = open(argv[2], O_WRONLY)) == -1, "dest open failure");
    
    char* line = NULL;
    size_t len = 0;
    int offset;
    char* word;

    while(getline(&line, &len, src) != -1){
        offset = atoi(line[0]);
        word = calloc(sizeof(char), MAX_SIZE);
        check_error(word == NULL, "calloc failure");
        for(int i = 2; (i - 2) < offset; i++){
            strcat(word[i-2], line[i]);
        }
        word[offset] = '\t';
        check_error(lseek(dest, offset, SEEK_SET) == -1, "lseek failure");
        check_error(write(dest, word, len - 3) == -1, "write failure");
        free(word);
    }


    free(line);
    close(src);
    close(dest);
    exit(EXIT_SUCCESS);
}