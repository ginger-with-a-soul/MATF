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
	
	osAssert(argc == 4, "Usage: ./3 -[fd] filePath permissions");
	
	long mode = strtol(argv[3], NULL, 8);
	mode_t oldUmask = umask(0);
	
	if (!strcmp(argv[1], "-f")) {
		int fd = 0;
		osAssert((fd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, mode)) != -1, "open failed");
		close(fd);
	}
	else if (!strcmp(argv[1], "-d")) {
		osAssert(mkdir(argv[2], mode) != -1, "mkdir failed");
	}
	else {
		osAssert(false, "wrong file type");
	}
	
	umask(oldUmask);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
