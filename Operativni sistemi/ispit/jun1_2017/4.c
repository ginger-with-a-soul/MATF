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
	
	osAssert(argc == 2, "./4 filePath");
	int lockCnt = 0;
	
	FILE* f = fopen(argv[1], "r+");
	osAssert(f != NULL, "fopen failed");
	
	int fd = fileno(f);
	osAssert(fd != -1, "fileno failed");
	
	struct flock lock;
	char buf[MAX_SIZE];
	
	while (!feof(f)) {
		
		char* error = buf;
		memset(buf, 0, MAX_SIZE);
		fscanf(f, "%s", buf);
		int num = strtol(buf, &error, 10);
		
		// not a number
		if (error == buf || *error != '\0') {
			continue;
		}
		
		int len = strlen(buf);
		
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = ftell(f);
		lock.l_len = -len;
		
		int result = fcntl(fd, F_SETLK, &lock);
		
		if (result == -1) {
			if (errno != EACCES && errno != EAGAIN) {
				osAssert(0, "lock failed");
			}
		}
		else {
			lockCnt++;
		}
	}
	
	// unlock file
	lock.l_type = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	osAssert(fcntl(fd, F_SETLK, &lock) != -1, "unlocking failed");
	
	printf("%d\n", lockCnt);
	
	fclose(f);
		
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNum) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNum);
	
	exit(EXIT_FAILURE);
}
