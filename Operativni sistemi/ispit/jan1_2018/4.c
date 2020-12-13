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
	int active = nfds;

	struct pollfd* fds = malloc(nfds * sizeof (struct pollfd));
	check_error(fds == NULL, "malloc() failure");

	int* charCount = malloc(sizeof(int) * nfds);
	check_error(charCount == NULL, "malloc() failure");

	char buffer[MAX_SIZE];

	for(int i = 0; i < nfds; i++){
		int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
		check_error(fd == -1, "open() failure");
		fds[i].fd = fd;
		fds[i].events = POLLIN;
		fds[i].revents = 0;
		charCount[i] = 0;
	}

	while(active){
		int ret = poll(fds, nfds, -1);
		check_error(ret == -1, "poll() failure");

		if(ret > 0){
			for(int i = 0; i < nfds; i++){
				if(fds[i].revents & POLLIN){
					ssize_t bytesRead = 0;
					while((bytesRead = read(fds[i].fd, buffer, MAX_SIZE)) > 0){
						buffer[bytesRead] = 0;
						charCount[i] += bytesRead;
					}
					check_error(bytesRead == -1, "read() failure");
					fds[i].revents = 0;
				}
				if(fds[i].revents & (POLLHUP | POLLERR)){
					check_error(close(fds[i].fd) == -1, "close() failuer");
					fds[i].fd = -1;
					fds[i].events = 0;
					fds[i].revents = 0;
					active -= 1;
				}
			}
		}
	}

	int max = 0;
	for(int i = 1; i < nfds; i++){
		if(charCount[max] < charCount[i]){
			max = i;
		}
	}

	char* pathname = strrchr(argv[max + 1], '/');
	if(pathname == NULL){
		printf("%s\n", argv[max + 1]);
	}
	else{
		printf("%s\n", pathname + 1);
	}

	free(charCount);
	free(fds);

	exit(EXIT_SUCCESS);
}