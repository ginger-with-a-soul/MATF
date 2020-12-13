/* Program ilustruje pokretanje ls komande i brojanje linije iz parent-a */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

#define RD_END (0)
#define WR_END (1)	

int main(int argc, char** argv) {
	
	/* kreiramo pajp */
	int cld2par[2];
	check_error(pipe(cld2par) != -1, "...");
	
	/* kreiramo child proces */
	pid_t pid = fork();
	check_error(pid != -1, "fork failed");
	
	if (pid > 0) {
		
		/* zatvaramo stranu pajpa koja nam ne treba */
		close(cld2par[WR_END]);
		
		char* line = NULL;
		size_t lineLen = 0;
		int lineCnt = 0;
		
		/* otvaramo stream nad RD stranom pajpa */
		FILE* f = fdopen(cld2par[RD_END], "r");
		
		/* citamo liniju po liniju koju nam salje ls komanda */
		while (getline(&line, &lineLen, f) != -1) {
			
			lineCnt++;
			
			printf("%d: %s", lineCnt, line);
		}
		
		/* oslobadjamo resurse */
		free(line);
		fclose(f);
	}
	else {
		
		close(cld2par[RD_END]);
		
		/* preusmeravamo fajl deskriptore. ono sto ce exec-ovani proces smatrati svojim stdout-om
		 * ce ustvari biti kraj pajpa za pisanje i na taj nacin smo preusmerili izlaz ls komande
		 * parentu
		 */
		check_error(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "...");
		
		/* execujemo ls */
		check_error(execlp("ls","ls","-l", NULL) != -1, "...");
		
		exit(EXIT_FAILURE);
	}
	
	/* obradjujemo zombije */
	int status = 0;
	check_error(wait(&status) != -1, "...");
	
	/* proveravamo exit status child procesa, tj. ls komande*/
	if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
		
		printf("All ok\n");
	}
	else {
		printf("Not ok\n");
	}
	exit(EXIT_SUCCESS);
}
			
