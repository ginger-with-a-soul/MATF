#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <poll.h>

#define check_error(expr, user_msg) \
    do { \
        if (!(expr)) { \
            perror(user_msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define MAX_SIZE (1024)

int main(int argc, const char *argv[])
{
    check_error(argc > 1, "argumenti");

    int nfds = argc - 1;
    int active_fifos = nfds;

    struct pollfd* fds = malloc(nfds * sizeof (struct pollfd));
    check_error(fds != NULL, "malloc");

    int* count = malloc(nfds * sizeof (int));
    check_error(count != NULL, "malloc");

    char buf[MAX_SIZE];

    for (int i = 0; i < nfds; i++) {
        int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        check_error(fd != -1, "open");

        fds[i].fd = fd;
        fds[i].events = POLLIN;
        fds[i].revents = 0;
    }

    while (active_fifos) {
        int ret = poll(fds, nfds, -1);
        check_error(ret != -1, "poll");

        if (ret > 0) {
            for (int i = 0; i < nfds; i++) {
                if (fds[i].revents & POLLIN) {
                    ssize_t read_bytes = 0;
                    while((read_bytes = read(fds[i].fd, buf, MAX_SIZE)) > 0) {
                        
                        buf[read_bytes] = 0;

                        for (int j = 0; buf[j]; j++) {
                            if (buf[j] == 'a') {
                                count[i]++;
                            }
                        }
                    }
                    check_error(read_bytes != -1, "read");
                    fds[i].revents = 0;
                }
                if (fds[i].revents & (POLLHUP | POLLERR)) {
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    fds[i].events = 0;
                    fds[i].revents = 0;
                    active_fifos--;
                }
            }
        }
    }

    int max_index = 0;
    for (int i = 1; i < nfds; i++) {
        if (count[max_index] < count[i]) {
            max_index = i;
        }
    }

    char* filename = strrchr(argv[max_index + 1], '/');
    if (filename == NULL) {
        printf("%s %d\n", argv[max_index + 1], count[max_index]);
    } else {
        printf("%s %d\n", filename + 1, count[max_index]);
    }
    
    free(count);
    free(fds);
    exit(EXIT_SUCCESS);
}
