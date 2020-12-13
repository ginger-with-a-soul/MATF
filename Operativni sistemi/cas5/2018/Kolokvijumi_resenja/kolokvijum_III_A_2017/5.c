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
#include <ftw.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
	do { \
		if (!(expr)) \
			osErrorFatal(userMsg); \
	} while (0)
	
void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber);

int total = 0;
int reg_cnt = 0;
int dir_cnt = 0;
int fifo_cnt = 0;
int chr_cnt = 0;
int blk_cnt = 0;
int sck_cnt = 0;
int lnk_cnt = 0;

int osProcessDir(const char* filePath, const struct stat* sb, int typeFlag, struct FTW* ftwBuf) {
	
	if (S_ISREG(sb->st_mode)) {
		reg_cnt++;
	}
	else if (S_ISDIR(sb->st_mode)) {
		dir_cnt++;
	}
	else if (S_ISCHR(sb->st_mode)) {
		chr_cnt++;
	}
	else if (S_ISBLK(sb->st_mode)) {
		blk_cnt++;
	}
	else if (S_ISFIFO(sb->st_mode)) {
		fifo_cnt++;
	}
	else if (S_ISLNK(sb->st_mode)) {
		lnk_cnt++;
	}
	else if (S_ISSOCK(sb->st_mode)) {
		sck_cnt++;
	}
	
	total++;
	
	return 0;
}

int main(int argc, char** argv) {
	
	osAssert(argc == 2, "Usage: ./5 dirPath");
	
	osAssert(nftw(argv[1], osProcessDir, 50, FTW_PHYS) != -1, "nftw failed");
	
	printf("%d %d %d %d %d %d %d %d\n", reg_cnt, dir_cnt, chr_cnt, blk_cnt, lnk_cnt, fifo_cnt, sck_cnt, total);
	
	exit(EXIT_SUCCESS);
}

void osErrorFatalImpl(const char* userMsg, const char* fileName, const char* functionName, const int lineNumber) {
	
	perror(userMsg);
	
	fprintf(stderr, "File name: %s\nFunction name: %s\nLine number: %d\n", fileName, functionName, lineNumber);
	
	exit(EXIT_FAILURE);
}
