#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <sys/epoll.h>

#define MAX_SIZE (1024)
#define MAX_EVENT (10)

typedef struct {
	int fd;
	int index;
} data_t;

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\

int main(int argc, char** argv){

	check_error(argc < 2 , "invalid arg count");

	int nfds = argc - 1;

	int epFD = epoll_create(nfds);
	check_error(epFD == -1, "epoll_create() failure");

	ssize_t* totalBytes = malloc(sizeof(ssize_t) * nfds);
	check_error(totalBytes == NULL, "malloc() failure");

	struct epoll_event ev;
	struct epoll_event events[MAX_EVENT];
	char buffer[MAX_SIZE];

	for(int i = 0; i < nfds; i++){
		int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
		check_error(fd == -1, "open() failure");

		data_t* data = malloc(sizeof(data_t));
		check_error(data == NULL, "malloc() failure");

		data->fd = fd;
		data->index = i;

		ev.events = EPOLLIN;
		ev.data.ptr = (void*) data;

		check_error(epoll_ctl(epFD, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll_ctl() failure");
	}

	while(nfds){
		int ready = epoll_wait(epFD, events, MAX_EVENT, -1);
		check_error(ready == -1, "epoll_wait() failure");

		for(int i = 0; i < ready; i++){
			if(events[i].events & EPOLLIN){
				ssize_t bytesRead = 0;
				

			}

			if(events[i].events & (EPOLLIN | EPOLLERR)){

			}
		}
	}



	


	exit(EXIT_SUCCESS);
}