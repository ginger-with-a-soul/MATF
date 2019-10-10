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

void deep_copy(struct passwd *src, struct passwd *dest);
void free_copy(struct passwd *copy);

int main(int argc, char** argv){
	check_error(argc != 2, "Invalid arg count...\nTerminating!\n");

	struct passwd* src;
	check_error((src = getpwnam(argv[1])) == NULL, "arg[1] is invalid...\nTerminating!\n");

	struct passwd* dest = malloc(sizeof(struct passwd));
	check_error(dest == NULL, "malloc() failure...\nTerminating!\n");

	deep_copy(src, dest);
	

	fprintf(stdout, "Username: %s\n", dest->pw_name);
	fprintf(stdout, "Password: %s\n", dest->pw_passwd);
	fprintf(stdout, "User ID: %li\n", (__intmax_t) dest->pw_uid);
	fprintf(stdout, "Group ID: %li\n", (__intmax_t) dest->pw_gid);
	fprintf(stdout, "User info: %s\n", dest->pw_gecos);
	fprintf(stdout, "Home directory: %s\n", dest->pw_dir);
	fprintf(stdout, "Shell program: %s\n", dest->pw_shell);

	free_copy(dest);

	exit(EXIT_SUCCESS);
}

void deep_copy(struct passwd *src, struct passwd *dest){
	dest->pw_name = strdup(src->pw_name);
	dest->pw_passwd = strdup(src->pw_passwd);
	dest->pw_uid = src->pw_uid;
	dest->pw_gid = src->pw_gid;
	dest->pw_gecos = strdup(src->pw_gecos);
	dest->pw_dir = strdup(src->pw_dir);
	dest->pw_shell = strdup(src->pw_shell);
}

void free_copy(struct passwd *copy){
	free(copy->pw_name);
	free(copy->pw_passwd);
	free(copy->pw_gecos);
	free(copy->pw_dir);
	free(copy->pw_shell);
}
