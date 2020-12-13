/* program ilustruje razlicite modove baferisanja 
 * kao i preusmeravanje fajol deskriptora
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)
	
int main(int argc, char** argv) {
	
	/* postavljamo mod baferisanja na stdout 
	 * probajte sva tri da biste videli razlike */

	//check_error(setvbuf(stdout, NULL, _IONBF, 0) == 0, "...");
	//check_error(setvbuf(stdout, NULL, _IOLBF, 0) == 0, "...");
	check_error(setvbuf(stdout, NULL, _IOFBF, 0) == 0, "...");
	
	printf("%s", "Neka poruka");
	
	/* kreiramo neki fajl */
	int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check_error(fd != -1, "open failed");
	
	/* pamtimo stdout fajl deskriptor */
	int fdCpy = dup(STDOUT_FILENO);
	check_error(fdCpy != -1, "dup failed");
	
	/* preusmeravmo stdout na fajl. posledica ovoga je da ce printf umesto na konzolu ici u fajl */
	check_error(dup2(fd, STDOUT_FILENO) != -1, "dup2 failed"); 
	printf("Ova poruka ide u fajl");
	
	/* fflush pod komentar samo za fully buffered mod */
	//fflush(NULL);
	
	/* vracamo ponovo ekran na stdout */
	check_error(dup2(fdCpy, STDOUT_FILENO) != -1, "dup2 failed"); 
	printf("Ova poruka ide na konzolu\n");
	
	close(fd);
	
	exit(EXIT_SUCCESS);
}