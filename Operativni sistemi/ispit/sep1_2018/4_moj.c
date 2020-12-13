#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <poll.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\

int main(int argc, char** argv){

	check_error(argc < 2, "invalid arg count");
	int nfds  = argc - 1;
	int left = nfds;

	struct pollfd* fds = malloc(nfds * sizeof (struct pollfd));
	check_error(fds == NULL, "malloc() failure");

	int* count = malloc(sizeof(int) * nfds);
	check_error(count == NULL, "malloc() failure");

	char buffer[MAX_SIZE];

	for(int i = 0; i < nfds; i++){
		int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
		check_error(fd == -1, "open() failure");
		fds[i].fd = fd;
		fds[i].events = POLLIN;
		fds[i].revents = 0;
		count[i] = 0;
	}

	while(left){
		int ret = poll(fds, nfds, -1);
		check_error(ret == -1, "poll() failure");

		if(ret > 0){
			for(int i = 0; i < nfds; i++){
				if(fds[i].revents & POLLIN){
					ssize_t bytesRead = 0;
					while((bytesRead = read(fds[i].fd, buffer, MAX_SIZE)) > 0){
						buffer[bytesRead] = 0;
						
						for(int j = 0; buffer[j]; j++){
							if(buffer[j] == 'a'){
								count[i]++;
							}
						}
					}
					check_error(bytesRead == -1, "read() failure");
					fds[i].revents = 0;

				}
				if(fds[i].revents & (POLLHUP | POLLERR)){
					check_error(close(fds[i].fd) == -1, "close() failure");
					fds[i].fd = -1;
					fds[i].events = 0;
					fds[i].revents = 0;
					left -= 1;
				}
			}
		}
	}

	int max = 0;
	for(int i = 1; i < nfds; i++){
		if(count[max] < count[i]){
			max = i;
		}
	}

	char* filename = strrchr(argv[max + 1], '/');
	if(filename == NULL){
		printf("%s %d\n", argv[max + 1], count[max]);
	}
	else{
		printf("%s %d\n", filename + 1, count[max]);
	}

	free(fds);
	free(count);

	exit(EXIT_SUCCESS);
}