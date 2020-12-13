#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <string.h>
#include <dirent.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

char* extension;

bool traverseDir(const char* filePath, int* sum);

int main(int argc, char** argv) {
	
	osAssert(argc == 3, "Usage: ./5 dirPath extension");
	
	struct stat fInfo;
	osAssert(stat(argv[1], &fInfo) != -1, "stat failed");
	
	osAssert(S_ISDIR(fInfo.st_mode), "needs to be a directory");
	
	extension = argv[2];
	int sum = 0;
	
	osAssert(traverseDir(argv[1], &sum), "traversal faield");
	
	printf("%d\n", sum);	
	
	exit(EXIT_SUCCESS);
}

bool traverseDir(const char* filePath, int* sum) {
	
	struct stat fInfo;
	if (stat(filePath, &fInfo) == -1)
		return false;
		
	char* ext = strrchr(filePath, '.');
	
	if (ext != NULL && !strcmp(extension, ext)) {
		(*sum)++;
	}
	
	if (!S_ISDIR(fInfo.st_mode))
		return true;
		
	DIR* dir = opendir(filePath);
	if (dir == NULL)
		return false;
		
	if (chdir(filePath) == -1)
		return false;
		
	struct dirent* dirEntry = NULL;
	while ((dirEntry = readdir(dir)) != NULL) {
		
		if (!strcmp(dirEntry->d_name, "..") || !strcmp(dirEntry->d_name, ".")) {
			
			continue;
		}
		
		bool success = traverseDir(dirEntry->d_name, sum);
		
		if (!success)
			return false;
	}
		
	if (chdir("..") == -1)
		return false;
	
	if (closedir(dir) == -1)
		return false;
		
	return true;
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
