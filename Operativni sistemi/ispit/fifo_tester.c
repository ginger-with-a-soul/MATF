#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#define check_error(expr, user_msg) \
    do { \
        if (!(expr)) { \
            perror(user_msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX_SIZE 1024

int main(int argc, const char *argv[])
{
    check_error(argc == 2, "argumenti");

    check_error(mkfifo(argv[1], 0644) != -1, "mkfifo");

    int fd = open(argv[1], O_WRONLY);
    check_error(fd != -1, "open");

    char buf[MAX_SIZE];
    char c;
    do {
        ssize_t read_bytes = read(STDIN_FILENO, buf, MAX_SIZE);
        check_error(read_bytes != -1, "read");

        check_error(write(fd, buf, read_bytes) != -1, "write");
        
        printf("Nastavi(y/n): ");
        c = getchar();
    } while (c != 'n');

    close(fd);
    exit(EXIT_SUCCESS);
}
