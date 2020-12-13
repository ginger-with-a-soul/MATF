/* Program brise fajl sa zadate putanje
 * Tip fajla i putanja do fajla se prosledjuje kao
 * argumenti komandne linije.
 *
 * Primer poziva:
 * ./rmfile -f test.txt
 * ./rmfile -d dir1
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	
	/* provera broja argumenata */
	if (argc != 3) {
		
		fprintf(stderr, "./rmfile -[fd] path\n");
		exit(EXIT_FAILURE);
	}
	
	/* ukoliko se radi o regularnom fajlu */
	if (!strcmp("-f", argv[1])) {
		/* uklanjamo ga sa unlink */
		if (unlink(argv[2]) == -1) {
			fprintf(stderr, "unlink failed\n");
			exit(EXIT_FAILURE);
		}
	}
	/* ukoliko se radi o direktorijumu */
	else if (!strcmp("-d", argv[1])) {
		/* uklanjamo ga sa rmdir
		 *
		 * BITNO:
		 * rmdir brise iskljucivo prazne direktorijume
		 */
		if (rmdir(argv[2]) == -1){
			fprintf(stderr, "rmdir failed\n");
			exit(EXIT_FAILURE);
		}
	}
	/* ako je korisnik prosledio bilo koju dugu opciju
	 * prekidamo program 
	 */
	else {
		fprintf(stderr, "-f or -d\n");
		exit(EXIT_FAILURE);
	}
	
	/* zavrsvanje sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}
