/* program ilustruje formatiranu komunikaciju izmedju provesa */
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
	
#define RD_END		(0)
#define WR_END 		(1)
#define MAX_SIZE (1024)	
	
int main(int argc, char** argv) {
	
	/* kreiramo pajp */
	int par2cld[2];
	check_error(pipe(par2cld) != -1, "pipe failed");
	
	/* kreiramo dete proces */
	pid_t pid = fork();
	check_error(pid != -1, "fork failed");
	
	if (pid > 0) { // parent
		close(par2cld[RD_END]);
		
		char* message = "Neka poruka";
		int number = 239847;
		
		/* otvaramo stream nad fajl deskriptorom koji opisuje WR stranu pajpa */
		FILE* f = fdopen(par2cld[WR_END], "w");
		check_error(f != NULL, "fdopen failed");
		
		/* saljemo formatiranu poruku childu pomocu stream-a */
		fprintf(f, "%s: %d\n",message, number);
		
		/* zatvaramo stream. zatvaranjem stream-a zatvara se i fajl deskriptor nad kojim je stream otvoren */
		fclose(f);
	}
	else { //child
		
		close(par2cld[WR_END]);
		
		/* otvaramo stream nad fajl deskriptorom koji opisuje RD stranu pajpa */
		FILE* f = fdopen(par2cld[RD_END], "r");
		check_error(f != NULL, "fdopen failed");
		
		/* citamo poruku koju salje parent */
		char buffer[MAX_SIZE];
		check_error(fgets(buffer, MAX_SIZE, f) != NULL, "fgets");
		
		/* stampamo poruku */
		printf("Child: %s\n", buffer);
		
		/* zatvaramo stream */
		fclose(f);
		
		/* child zavrsava sa radom */
		exit(EXIT_SUCCESS);
	}
	
	/* obrajdujemo zombije */
	int status;
	check_error(wait(&status) != -1, "wait failed");
	
	exit(EXIT_SUCCESS);
}
			
