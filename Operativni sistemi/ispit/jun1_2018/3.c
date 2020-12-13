#define _XOPEN_SOURCE 700
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<stdint.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#include<sys/wait.h>
#include<string.h>
#include "oserror.h"

#define RD_END (0)
#define WR_END (1)

int main(int argc, char **argv)
{
	((void)argv);
	os_assert(argc == 1, "wrong number of argumnets");
	int childWparentR[2];
	/* pravimo pajp */
	os_assert(pipe(childWparentR) != -1, "pipe failed");
	
	/* krairamo dete proces */
	pid_t cpid = fork();
	os_assert(cpid != -1, "fork failed");
	
	
	if (cpid == 0) { //child
		/* u detetu zatvaramo stranu pajpa koja nam ne treba */
		close(childWparentR[RD_END]);
		/* preusmeravamo izlaz */
		int old = dup2(childWparentR[WR_END], STDOUT_FILENO);
		os_assert(old != -1, "dup failed");
		/* execujemo komandu */
		os_assert(execlp("ls", "ls", "-l", NULL) != -1, "exec failed");
	} else { // parent
	
		/* u parentu zatvaramo stranu pajpa koja nam ne treba */
		close(childWparentR[WR_END]);
		/* cekamo da se dete zavrsi i hvatamo status zavrsetka */
		int status;
		os_assert(wait(&status) != -1, "wait failed");
		
		/* ako je dete pozvalo exit i kontrolisano se zavrsilo */
		if (WIFEXITED(status)) {
			/* citamo exit kod */
			int exit_status = WEXITSTATUS(status);
			/* ako je ok */
			if (exit_status == EXIT_SUCCESS) {
				
				/* pridruzujemo strim fajl deskriptoru */
				FILE *f = fdopen(childWparentR[RD_END], "r");
				os_assert(f != NULL, "fdopen failed");
				
				char *lineptr = NULL;
				size_t n = 0;
				
				/* ignorisemo prvu liniju -> total ...*/
				os_assert(getline(&lineptr, &n, f) != -1, "failed getline");
				
				/* parsiramo liniju po liniju */
				while (getline(&lineptr, &n, f) != -1) {
					/* ako su prava pristupa za ostale rwx */
					if (lineptr[7] == 'r' && lineptr[8] == 'w'&& lineptr[9] == 'x') {
						/* stampamo samo ime fajla */
						char *filename = strrchr(lineptr, ' ');
						os_assert(filename != NULL, "failed");
						printf("%s", filename + 1);
					}
				}
				/* oslobadjamo resurse */
				os_assert(!ferror(f), "error reading ffrom file");
				free(lineptr);
				fclose(f);
			} else {
				/* ako nije, vracamo odgovarajuci status */
				close(childWparentR[RD_END]);
				printf("neuspeh\n");
				exit(exit_status);
			}
		} else {
			/* ako nije, prekidamo program */
			close(childWparentR[RD_END]);
			os_assert(false, "katastrofa");
		}	
	}
	exit(EXIT_SUCCESS);
}