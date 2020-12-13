#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <errno.h>


#define MAX_SIZE (1024)
#define check_error(exp, usrMsg)\
	do {\
		if(exp){\
			perror(usrMsg);\
			printf("\n");\
			exit(EXIT_FAILURE);\
		}\
	} while(0);\



int main(int argc, char** argv){

	check_error(argc != 2, "invalid arg count");

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) == -1, "stat() failure");
	check_error(!S_ISREG(fInfo.st_mode), "not a regular file");

	FILE* f = fopen(argv[1], "r+");
	check_error(f == NULL, "fopen() failure");

	int fd = fileno(f);
	check_error(fd == -1, "fileno() failure");

	char word[MAX_SIZE];
	unsigned mirroredNum = 0, lockedNum = 0; 	 	
	
	struct flock lock;

	while(fscanf(f, "%s", word) != EOF){
		int len = strlen(word);

		char* mirroredWord = malloc(sizeof(char) * (len + 1));
		check_error(mirroredWord == NULL, "malloc() failure");

		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_CUR;
		lock.l_start = ftell(f);
		lock.l_len = -len;

		check_error(fcntl(fd, F_GETLK, &lock) == -1, "fcntl()");


		if(lock.l_type != F_RDLCK && lock.l_type != F_WRLCK){
			int j = 0;
			for(int i = len - 1; i >= 0; i--){
				mirroredWord[j++] = word[i];
			}
			mirroredWord[j] = 0;

			check_error(fseek(f, -len, SEEK_CUR) == -1, "lseek() failure");
			fprintf(f, "%s", mirroredWord);
			free(mirroredWord);

			mirroredNum += 1;
		}
		else{
			lockedNum += 1;
		}

	}

	check_error(!feof(f), "not feof(f)");

	printf("%u %u\n", mirroredNum, lockedNum);

	fclose(f);

	exit(EXIT_SUCCESS);
}