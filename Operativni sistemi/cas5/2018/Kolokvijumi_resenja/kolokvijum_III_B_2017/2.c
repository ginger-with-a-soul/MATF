#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <string.h>
#include <math.h>

#define SECS_PER_DAY (24*60*60)

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

int main(int argc, char** argv) {
	
	osAssert(argc == 3, "Usage: ./1 filePath size");
	
	struct stat fInfo;
	osAssert(stat(argv[1], &fInfo) != -1, "stat failed");
	
	char* nameCandidate = strrchr(argv[1], '/');
	double size = 0;
	char* s;
	if (!strcmp(argv[2], "KB")) {
		size = (double)(fInfo.st_size*1.0/1024);
		s = "KB";
	}
	else if (!strcmp(argv[2], "MB")) {
		size = (double)(fInfo.st_size*1.0/(1024*1024));
		s = "MB";
	}
	else if (!strcmp(argv[2], "GB")) {
		size = (double)(fInfo.st_size*1.0/(1024*1024*1024));
		s = "GB";
	}
	else {
		osAssert(false, "wrong size option");
	}
	
	size = ceil(size);
	printf("%s %d%s\n", nameCandidate != NULL ? nameCandidate + 1 : argv[1], (int)size, s);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
