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
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

void osProcessFile(const char* filePath, const char* mode);

int main(int argc, char** argv) {
	
	osAssert(argc == 3, "Usage: ./4 -[rwa] filePath");
	
	osAssert(!strcmp(argv[1], "-r") || !strcmp(argv[1], "-w") || !strcmp(argv[1], "-a"), "Invalid argument");
	
	osProcessFile(argv[2], argv[1]);
	
	exit(EXIT_SUCCESS);
}

void osProcessFile(const char* filePath, const char* mode) {
	
	int inFd, outFd;
	
	switch (mode[1]) {
		case 'r':
			inFd = open(filePath, O_RDONLY);
			osAssert(inFd != -1, "open failed");
			outFd = STDOUT_FILENO;
			break;
		case 'w':
			outFd = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			osAssert(outFd != -1, "open failed");
			inFd = STDIN_FILENO;		
			break;
		case 'a':
			outFd = open(filePath, O_WRONLY | O_CREAT | O_APPEND, 0644);
			osAssert(outFd != -1, "open failed");
			inFd = STDIN_FILENO;		
			break;
	}
	
	size_t bufSize = 1<<13U;
	char* buf = malloc(bufSize);
	osAssert(buf != NULL, "allocation failed");
	
	int readBytes = 0;
	while ((readBytes = read(inFd, buf, bufSize)) > 0) {
		
		if (write(outFd, buf, readBytes) != readBytes) {
			
			free(buf);
			osAssert(false, "write failed");
		}
	}
	
	osAssert(readBytes == 0, "read failed");
	
	free(buf);
	switch (mode[1]) {
		case 'r':
			close(inFd);
			break;
		case 'w':
			close(outFd);
			break;
		case 'a':
			close(outFd);
			break;
	}
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
