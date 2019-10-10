#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include <pwd.h>

#define MAX_SIZE (1024)

#define check_error(exp, usrMsg)\
	do{\
		if(exp){\
			perror(usrMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

void print_details(struct passwd* usr);

int main(int argc, char** argv){
	check_error(argc != 1, "Invalid arg count...\nTerminating!\n");

	struct passwd* current;

	setpwent();

	while((current = getpwent()) != NULL){
		print_details(current);
	}

	endpwent();

	exit(EXIT_SUCCESS);
}

void print_details(struct passwd* usr){
	fprintf(stdout, "~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=\n");
	fprintf(stdout, "Username: %s\n", usr->pw_name);
	fprintf(stdout, "Password: %s\n", usr->pw_passwd);
	fprintf(stdout, "User ID: %li\n", (__intmax_t) usr->pw_gid);
	fprintf(stdout, "User info: %li\n", (__intmax_t) usr->pw_gecos);
	fprintf(stdout, "Home directory: %s\n", usr->pw_dir);
	fprintf(stdout, "Shell program: %s\n", usr->pw_shell);
}