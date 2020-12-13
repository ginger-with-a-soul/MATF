#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
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

#define MAX_EVENTS (10)
#define MAX_SIZE (1024)

typedef struct {
    int fd;
    int index;
}data_t;

int main(int argc, const char *argv[])
{
    check_error(argc > 1, "argumenti");

    int nfds = argc - 1;

    ssize_t* total_bytes = malloc(nfds * sizeof (ssize_t));
    check_error(total_bytes != NULL, "malloc");

    int epoll_fd = epoll_create(nfds);
    check_error(epoll_fd != -1, "epoll_create");

    struct epoll_event ev;
    for (int i = 0; i < nfds; i++) {
        int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        check_error(fd != -1, "open");

        data_t* data = malloc(sizeof (data_t));
        check_error(data != NULL, "malloc");

        data->fd = fd;
        data->index = i;

        ev.events = EPOLLIN;
        ev.data.ptr =(void*) data;

        check_error(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) != -1, "epoll_ctl");
    }

    char buf[MAX_SIZE];
    struct epoll_event events[MAX_EVENTS];
    while (nfds > 0) {
        int ready = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        check_error(ready != -1, "epoll_wait");

        for (int i = 0; i < ready; i++) {
            data_t* data = (data_t*)    events[i].data.ptr;

            if (events[i].events & EPOLLIN) {
                ssize_t read_bytes = 0;
                while (read_bytes = read(data->fd, buf, MAX_SIZE)) {
                    total_bytes[data->index] += read_bytes;
                }
                check_error(read_bytes != -1, "read");
            }

            if (events[i].events & (EPOLLHUP | EPOLLERR)) {
                close(events[i].data.fd);
                free(data);
                nfds--;
            }
        }
    }

    int min_index = 0;
    for (int i = 0; i < argc - 1; i++) {
        if (total_bytes[min_index] > total_bytes[i]) {
            min_index = i;
        }
    }

    char* filename = strrchr(argv[min_index + 1], '/');
    if (filename == NULL) {
        printf("%s\n", argv[min_index + 1]);
    } else {
        printf("%s\n", filename + 1);
    }

    free(total_bytes);
    close(epoll_fd);
    exit(EXIT_SUCCESS);
}
