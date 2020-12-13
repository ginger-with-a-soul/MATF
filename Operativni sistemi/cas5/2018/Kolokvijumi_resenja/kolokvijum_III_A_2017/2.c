#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <pwd.h>
#include <grp.h>
#include <string.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Usage: ./2 filePath");
	
	struct stat fInfo;
	osAssert(stat(argv[1], &fInfo) != -1, "stat failed");
	
	char* username;
	struct passwd* pwd = getpwuid(fInfo.st_uid);
	osAssert(pwd != NULL, "getpwuid failed");
	username = malloc(strlen(pwd->pw_name) + 1);
	strcpy(username, pwd->pw_name);
	
	char* grpname;
	struct group* grp = getgrgid(fInfo.st_gid);
	osAssert(grp != NULL, "getgrgid failed");
	grpname = malloc(strlen(grp->gr_name) + 1);
	strcpy(grpname, grp->gr_name);
	
	printf("%s %s\n", username, grpname);
	
	free(username);
	free(grpname);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
