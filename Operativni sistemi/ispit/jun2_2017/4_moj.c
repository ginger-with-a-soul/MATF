#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <errno.h>
#include <poll.h>

#define MAX_SIZE (1024)

#define check_error(expr, user_msg) \
    do { \
        if (expr) { \
            perror(user_msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)



int main(int argc, const char* argv[]){

	check_error(argc < 2, "argumenti");

    int nfds = argc - 1;
    int active = nfds;

    struct pollfd* fds = malloc(nfds * sizeof (struct pollfd));
    check_error(fds == NULL, "malloc");

    int* counter = malloc(nfds * sizeof (int));
    check_error(counter == NULL, "malloc");

    FILE** streams = malloc(nfds * sizeof (FILE*));
    check_error(streams == NULL, "malloc");

	int x = 0;

	//  for (int i = 0; i < nfds; i++) {
        // int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        // check_error(fd == -1, "open");
// 
        // streams[i] = fdopen(fd, "r");
        // check_error(streams[i] == NULL, "fdopen");
// 
        // fds[i].fd = fd;
        // fds[i].events = POLLIN;
        // fds[i].revents = 0;
        // 
        // counter[i] = INT_MIN;
    // }

	for(int i = 0; i < nfds; i++){
		int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
		check_error(fd == -1, "open() failure");
		streams[i] = fdopen(fd, "r");
        check_error(streams[i] == NULL, "fdopen");
		fds[i].fd = fd;
		fds[i].events = POLLIN;
		fds[i].revents = 0;
		counter[i] = INT_MIN;
	}

	

	while(active) {
        int res = poll(fds, nfds, -1);
        check_error(res == -1, "poll");

		if(res > 0){
			for (int i = 0; i < nfds; i++) {
            if (fds[i].revents & POLLIN) {
                int num;
                while (fscanf(streams[i], "%d", &num) == 1) {
                    if (counter[i] < num) {
                        counter[i] = num;
                    }
                }

                fds[i].revents = 0;
            }

				if (fds[i].revents & (POLLHUP | POLLERR)) {
                close(fds[i].fd);
                fclose(streams[i]);
                fds[i].fd = -1;
                fds[i].events = 0;
                fds[i].revents = 0;
                active--;
            }
			}
		}
	}

	int max_index = 0;
    for (int i = 0; i < nfds; i++) {
        if (counter[max_index] < counter[i]) {
            max_index = i;
        }
    }

	char* filename = strrchr(argv[max_index + 1], '/');
    if (filename == NULL) {
        printf("%d %s\n", counter[max_index], argv[max_index + 1]);
    } else {
        printf("%d %s\n", counter[max_index], filename + 1);
    }

	free(streams);
	free(counter);
	free(fds);

	exit(EXIT_SUCCESS);
}