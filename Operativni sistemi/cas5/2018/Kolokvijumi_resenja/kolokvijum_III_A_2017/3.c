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

int main(int argc, char** argv) {
	
	osAssert(argc == 4, "Usage: ./3 -[d|f] filePath mode");
	
	long mode = strtol(argv[3], NULL, 8);
	
	if (!strcmp(argv[1], "-f")) {
		int fd = open(argv[2], O_RDONLY | O_CREAT, mode);
		osAssert(fd != -1, "open failed");
		close(fd);
	}
	else if (!strcmp(argv[1], "-d")) {
		
		int returnVal = mkdir(argv[2], mode);
		
		if (returnVal == -1) {
			if (errno != EEXIST) {
				osAssert(false, "mkdir failed");
			}
		}
	}
	else {
		errno = EINVAL;
		osAssert(false, "Wrong option");
	}
	
	osAssert(chmod(argv[2], mode) != -1, "chmod failed");
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
