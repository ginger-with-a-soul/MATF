#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <string.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

int main(int argc, char** argv) {
	
	osAssert(argc == 4, "Usage: ./4 filePath offset noOfChars");
	
	struct stat fInfo;
	osAssert(stat(argv[1], &fInfo) != -1, "stat failed");
	
	osAssert(S_ISREG(fInfo.st_mode), "needs to be regular");
	
	int fd = open(argv[1], O_RDONLY);
	osAssert(fd != -1, "open failed");
	
	int offset = atoi(argv[2]);
	int length = atoi(argv[3]);
	
	osAssert(lseek(fd, offset, SEEK_SET) != -1, "lseek failed");
	
	char* buffer = malloc(length+2);
	osAssert(buffer != NULL, "malloc failed");
	
	int readBytes = 0;
	while(length > 0) {
		
		readBytes = read(fd, buffer, length);
		osAssert(readBytes != -1, "read failed");
		
		osAssert(write(STDOUT_FILENO, buffer, readBytes) != -1, "write failed");

		length -= readBytes;
	}

	close(fd);
	free(buffer);
		
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
