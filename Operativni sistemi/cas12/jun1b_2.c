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
	} while(0)\

int main(int argc, char** argv){

	check_error(argc < 2, "Invalid arg count");

	int argNum = argc - 1;

	struct pollfd* pfd = malloc(sizeof(struct pollfd) * argNum);
	check_error(pfd == NULL, "malloc() failure");

	FILE** fstreams = malloc(sizeof(FILE*) * argNum);
	check_error(fstreams == NULL, "malloc() failure");

	for(int i = 0; i < argNum; i++){
		pfd[i].fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
		check_error(pfd[i].fd == -1, "open() failure");

		fstreams[i] = fdopen(pfd[i].fd, "r");
		check_error(fstreams[i] == NULL, "fdopen() failure");

		pfd[i].events = POLLIN | POLLERR | POLLHUP;
		pfd[i].revents = 0;
	}

	int init = 0;
	int max = 0;
	int num = argNum;
	char* name = NULL;
	int x;

	while(num){
		int retVal = poll(pfd, argNum, -1);
		check_error(retVal == -1, "poll() failure");
		for(int i = 0; i < argNum; i++){
			if(pfd[i].revents & POLLIN){
				while(fscanf(fstreams[i], "%i", &x) == 1){
					if(init){
						max = max > x? max : x;
						name = argv[i + 1];
					}
					else{
						max = x;
						init = 1;
						name = argv[i + 1];
					}
				}
				check_error(feof(fstreams[i]) == 0, "feof() failure");
				pfd[i].revents = 0;
			}
			else if(pfd[i].revents & (POLLHUP | POLLERR)){
				check_error(fclose(fstreams[i]) == EOF, "fclose() failure");
				pfd[i].fd = -1;
				pfd[i].events = 0;
				pfd[i].revents = 0;
				num -= 1;
			}
		}
	}

	char* fName = strrchr(name, '/');
	printf("Max %i is from the file %s\n", max, fName != NULL ? fName : name);

	free(pfd);
	free(fstreams);

	exit(EXIT_SUCCESS);
}