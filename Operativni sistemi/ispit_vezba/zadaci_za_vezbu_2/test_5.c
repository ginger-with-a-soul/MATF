#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <errno.h>
#include <string.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)

#define MAX_SIZE (1024)		

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum);

int main(int argc, char** argv) {
	
	int fd = open(argv[1], O_RDWR);
	osAssert(fd != -1, "open failed");
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 8;
	
	fcntl(fd, F_SETLK, &lock);
	
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 31;
	lock.l_len = 8;
	
	fcntl(fd, F_SETLK, &lock);
	
	getchar();
	
	close(fd);
		
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNum);
	
	exit(EXIT_FAILURE);
}
