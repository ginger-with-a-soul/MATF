#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <time.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			fprintf(stderr, "...\nTerminating!\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

void printFileInfo(const char* path, char** str);
char* getUserName(const uid_t userID);
char* getGroupName(const gid_t groupID);

int main(int argc, char** argv){
	check_error(argc != 2, "Invalid arg count...\nTerminating!\n");

	char* str = NULL;

	printFileInfo(argv[1], &str);

	fprintf(stdout, "%s\n", str);

	free(str);

	exit(EXIT_SUCCESS);
}

void printFileInfo(const char* path, char** str){
	errno = EINVAL;
	check_error(*str != NULL, "string had to be NULL initialized...\nTerminating!\n");
	errno = 0;

	struct stat fInfo;
	check_error(stat(path, &fInfo) == -1, "stat() failure");

	char* fInfoStr = calloc(MAX_SIZE, sizeof(char));
	check_error(fInfoStr == NULL, "calloc() failure");
	int totalBytes = 0;

	totalBytes += sprintf(fInfoStr + totalBytes, "%s ", "-rwxrwxrwx");

	switch(fInfo.st_mode & S_IFMT){
		case S_IFBLK: fInfoStr[0] = 'b'; break;
		case S_IFCHR: fInfoStr[0] = 'c'; break;
		case S_IFLNK: fInfoStr[0] = 'l'; break;
		case S_IFIFO: fInfoStr[0] = 'p'; break;
		case S_IFSOCK: fInfoStr[0] = 's'; break;
		case S_IFREG: fInfoStr[0] = '-'; break;
		case S_IFDIR: fInfoStr[0] = 'd'; break;
		default: break;
	}

	if(!(fInfo.st_mode & S_IRUSR)){
		fInfoStr[1] = '-';
	}
	if(!(fInfo.st_mode & S_IWUSR)){
		fInfoStr[2] = '-';
	}
	if(!(fInfo.st_mode & S_IXUSR)){
		fInfoStr[3] = '-';
	}
	if(!(fInfo.st_mode & S_IRGRP)){
		fInfoStr[4] = '-';
	}
	if(!(fInfo.st_mode & S_IWGRP)){
		fInfoStr[5] = '-';
	}
	if(!(fInfo.st_mode & S_IXGRP)){
		fInfoStr[6] = '-';
	}
	if(!(fInfo.st_mode & S_IROTH)){
		fInfoStr[7] = '-';
	}
	if(!(fInfo.st_mode & S_IWOTH)){
		fInfoStr[8] = '-';
	}
	if(!(fInfo.st_mode & S_IXOTH)){
		fInfoStr[9] = '-';
	}

	totalBytes += sprintf(fInfoStr + totalBytes, "%li ", (__intmax_t) fInfo.st_size);

	char* usrName = getUserName(fInfo.st_uid);
	totalBytes += sprintf(fInfoStr + totalBytes, "%s ", usrName);

	char* grName = getGroupName(fInfo.st_gid);
	totalBytes += sprintf(fInfoStr + totalBytes, "%s ", grName);

	char* strTime = ctime(&fInfo.st_mtime);
	totalBytes += sprintf(fInfoStr + totalBytes, "%s", strTime);

	*str = fInfoStr;
}

char* getGroupName(const gid_t groupID){
	struct group* grStruct;
	check_error((grStruct = getgrgid(groupID)) == NULL, "getgrgid() failure");
	char* string = malloc(strlen(grStruct->gr_name) + 1);
	check_error(string == NULL, "malloc() failure");
	strcpy(string, grStruct->gr_name);
	return string;
}

char* getUserName(const uid_t userID){
	struct passwd* pwdStruct;
	check_error((pwdStruct = getpwuid(userID)) == NULL, "getpwuid() failure");
	char* string = malloc(strlen(pwdStruct->pw_name) + 1);
	check_error(string == NULL, "malloc() failure\n");
	strcpy(string, pwdStruct->pw_name);
	return string;
}
