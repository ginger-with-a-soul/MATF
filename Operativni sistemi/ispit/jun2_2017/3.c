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
	
	osAssert(argc == 4, "./4 filePath word1 word2");
	int lockCnt = 0;
	
	FILE* f = fopen(argv[1], "r+");
	osAssert(f != NULL, "fopen failed");
	
	int fd = fileno(f);
	osAssert(fd != -1, "fileno failed");
	
	struct flock lock;
	char buf[MAX_SIZE];
	
	while (!feof(f)) {
		
		char* error;
		fscanf(f, "%s", buf);
		
		if (strcmp(buf, argv[2])) {
			continue;
		}
		
		int len = strlen(argv[2]);
		
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = ftell(f);
		lock.l_len = -len;
		
		int result = fcntl(fd, F_SETLK, &lock);
		
		if (result == -1) {
			if (errno != EACCES && errno != EAGAIN) {
				osAssert(0, "lock failed");
			}
			else {
				lockCnt++;
			}
		}
		else {
			osAssert(fseek(f, -len, SEEK_CUR) != -1, "fseek failed");
			fprintf(f, "%s", argv[3]);
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
