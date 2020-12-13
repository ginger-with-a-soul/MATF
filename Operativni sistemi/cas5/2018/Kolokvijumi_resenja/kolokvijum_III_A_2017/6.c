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
#include <limits.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

void osMoveFile(const char* src, const char* dest) {
	
	char* absSrc = realpath(src, NULL);
	osAssert(absSrc != NULL, "source file doesn't exist");
	char* absDest = realpath(dest, NULL);
	if (absDest != NULL) {
		osAssert(strcmp(absSrc, absDest) != 0, "same file");
	}
	
	free(absSrc);
	if (absDest != NULL)
		free(absDest);
	
	osAssert(rename(src, dest) != -1, "moving failed");
}

int main(int argc, char** argv) {
	
	osAssert(argc == 3, "Usage: ./6 srcPath destPath");
	
	osMoveFile(argv[1], argv[2]);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
