#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Usage: ./1 filePath");
	
	struct stat fInfo;
	osAssert(stat(argv[1], &fInfo) != -1, "stat failed");
	char s[] = "-rwxrwxrwx";
	
	if (S_ISDIR(fInfo.st_mode))
		s[0] = 'd';
	else if (S_ISREG(fInfo.st_mode))
		s[0] = '-';
	else 
		osAssert(false, "not regular or directory");
	
	if (!(fInfo.st_mode & S_IRUSR))
		s[1] = '-';
	if (!(fInfo.st_mode & S_IWUSR))
		s[2] = '-';
	if (!(fInfo.st_mode & S_IXUSR))
		s[3] = '-';
	
	if (!(fInfo.st_mode & S_IRGRP))
		s[4] = '-';
	if (!(fInfo.st_mode & S_IWGRP))
		s[5] = '-';
	if (!(fInfo.st_mode & S_IXGRP))
		s[6] = '-';
	
	if (!(fInfo.st_mode & S_IROTH))
		s[7] = '-';
	if (!(fInfo.st_mode & S_IWOTH))
		s[8] = '-';
	if (!(fInfo.st_mode & S_IXOTH))
		s[9] = '-';
	
	printf("%s\n", s);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
