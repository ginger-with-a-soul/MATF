	#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#define check_error(expr, userMsg) \
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while (0)

int main(int argc, char** argv) {
	
	check_error(argc == 2, "....");
	
	/* otvaramo fajl deskriptor */
	int fd = open(argv[1], O_RDWR);
	check_error(fd != -1, "...");
	
	/* pridruzujemo mu fajl strim */
	FILE* f = fdopen(fd, "r+");
	check_error(f != NULL, "...");
	int success = 0;
	int failure = 0;
	char buffer[1024];
	/* citamo rec po rec */
	while (fscanf(f, "%s", buffer) == 1) {
		
		/* navodimo parametre zakljucavanja */
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_CUR;
		lock.l_start = ftell(f);
		lock.l_len = -strlen(buffer);
		
		/* probamo da zakljucamo */
		if (fcntl(fd, F_SETLK, &lock) == -1) {
			/* ako razlog neuspeha nije drugi proces koji drzi katanac */
			if (errno != EACCES && errno != EAGAIN) {
				/* prekidamo program */
				check_error(0, "...");
			}
			/* ako jeste, uvecavamo brojac i idemo na narednu rec */
			failure++;
			continue;
		}
		else {
			
			/* ako smo uspeli */
			int n = strlen(buffer);
			char* s = malloc(n + 1);
			check_error(s != NULL, "...");
			
			/* obrcemo rec */
			int k = 0;
			for (int i = n-1; i >= 0; i--){
				s[k++] = buffer[i];
			}
			s[k] = 0;
			/* pomeramo ofset */
			fseek(f, -n, SEEK_CUR);
			/* upisujemo rec */
			fprintf(f, "%s", s);
			free(s);
			
			/* otkljucavamo rec */
			lock.l_type = F_UNLCK;
			check_error(fcntl(fd, F_SETLK, &lock) != -1, "...");
			success++;
		}
	}
	
	check_error(feof(f), "...");
	/* stampamo rezultate */
	printf("%d %d\n", success, failure);
	
	fclose(f);
	
	exit(EXIT_SUCCESS);
}
