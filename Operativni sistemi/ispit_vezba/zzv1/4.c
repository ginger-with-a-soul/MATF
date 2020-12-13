#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/epoll.h>
#include <signal.h>

#define MAX_SIZE (1024)
#define LENGHT (127)
#define MAX_EVENTS (8)

#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

int main(int argc, char** argv){

	check_error(argc != 2, "Invalid arg count");

	unsigned num = atoi(argv[1]);
	int epollFd = epoll_create(num);
	check_error(epollFd == -1, "epoll_create() failure");

	struct epoll_event currentEvent;
	char buffer[MAX_SIZE];

	for(int i = 0; i < num; i++){
		memset(&currentEvent, 0, sizeof(currentEvent));
		currentEvent.events |= EPOLLIN;

		memset(buffer, 0, MAX_SIZE);
		sprintf(buffer, "/tmp/%i", i);
		currentEvent.data.fd = open(buffer, O_RDONLY | O_NONBLOCK);
		check_error(currentEvent.data.fd == -1, "open() failure");
		check_error(epoll_ctl(epollFd, EPOLL_CTL_ADD, currentEvent.data.fd, &currentEvent) == -1, "epoll_ctl() failure");
	}

	struct epoll_event readyList[MAX_EVENTS];
	while(num){

		int numOfReadyEvents = epoll_wait(epollFd, readyList, MAX_EVENTS, EPOLL_TIMEOUT_BLCK);
		check_error(numOfReadyEvents == -1, "epoll_wait() failure");

		num--;
	}

	close(epollFd);

	exit(EXIT_SUCCESS);
}