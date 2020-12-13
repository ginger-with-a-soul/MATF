/* Program ilustruje multipleksiranje upotrebom poll interfejsa */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <string.h>
#include <poll.h>

#define check_error(expr,userMsg) \
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while (0)

#define MAX_SIZE (1024)

int main(int argc, char** argv) {
	
	check_error(argc > 1, "...");
	
	/* kreiramo niz struktura u kojima opisujemo sta hocemo da pratimo
	 * na svakom fajl deskriptoru
	 */ 
	int nfd = argc - 1;
	struct pollfd* fds = malloc(nfd*sizeof(struct pollfd));
	check_error(fds != NULL, "...");
	
	/* u petlji */
	for (int i = 0; i < argc-1; i++) {
		/* otvaramo fajl */
		int fd = open(argv[i+1], O_RDONLY | O_NONBLOCK);
		check_error(fd != -1, "...");
		/* pamtimo fajl deskriptor u strukturi */
		fds[i].fd = fd;
		/* definisemo akcije koje nadgledamo 
		 * POLLIN -> spreman je za citanja
		 * POLLERR | POLLHUP -> greske
		 */ 
		fds[i].events = POLLIN | POLLERR | POLLHUP;
		/* revents polje postavljamo na nulu, jer na pocetku nije
		 * moguce da bude registrovan bilo koji dogadjaj 
		 */ 
		fds[i].revents = 0;
	}
	
	/* u petlji */
	while (1) {
		
		/* cekamo da se desi akcija */
		int retVal = poll(fds, nfd, -1);
		check_error(retVal !=-1, "poll failed");
		
		/* u petlji proveravamo na kom fd-u se desila akcija */
		int breakLoops = 0;
		for (int i = 0; i < nfd; i++) {
			
			/* ako je spreman za citanje */
			if (fds[i].revents & POLLIN) {
				
				/* citamo prosledjenu poruku */
				char buffer[MAX_SIZE];
				int readBytes = read(fds[i].fd, buffer, MAX_SIZE);
				check_error(readBytes != -1, "...");
				/* terminiramo sadrzaj */
				buffer[readBytes] = 0;
				
				/* prikazujemo je na ekranu */
				printf("%d: %s\n", i, buffer);
				/* ako je u pitanju poruka za prekidanje */
				if (!strcmp(buffer, "quit\n")) {
					/* postavljamo flag i prekidamo petlju */
					breakLoops = 1;
					break;
				}
				
				/* obavezno resetujemo registrovani dogadjaj */
				fds[i].revents = 0;
			}
			/* ako se desila greska */
			else if (fds[i].revents & (POLLERR | POLLHUP)) {
				
				/* zatvaramo fajl deskriptor */
				close(fds[i].fd);
				/* i izbacujemo ga iz razmatranja */
				fds[i].fd = -1;
				fds[i].events = 0;
				fds[i].revents = 0;
			}		
		}
		
		/* ako se desio signal za kraj, prekidamo izvrsavanje */
		if (breakLoops)
			break;
	}
	
	/* zatvaramo preostale fajl desktiprore */
	for (int i = 0; i < nfd; i++) {
		if (fds[i].fd != -1)
			close(fds[i].fd);
	}
	
	/* oslobadjamo memoriju */
	free(fds);
	
		
	exit(EXIT_SUCCESS);
}
