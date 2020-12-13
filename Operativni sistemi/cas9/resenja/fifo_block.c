/* Program ilustruje neblokirajuci IO na vestacki nacin
 * Cilj zadatka je da proveri da li je neki drugi proces otvorio
 * imenovani pajp. 
 *
 * Podrazumevano ovo je blokirajuca operaciju, koja moze da se zavrsi
 * bez blokiranja upotrebom neblokirajuceg IO, tj. navodjenjem O_NONBLOCK
 * flaga prilikom otvaranja fajlova.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

int hasReadEnd(const char* path);

int hasWriteEnd(const char* path);

int main(int argc, char** argv) {
	
	check_error(argc == 3, "...");
	
	/* u zavisnosti od argumenta, proveravamo ili r ili w stranu pajpa */
	if (!strcmp(argv[1], "-r")) {
		int retVal = hasReadEnd(argv[2]);
		
		printf("Read end: %s\n", retVal == 1 ? "Yes" : "No");
	}
	else if (!strcmp(argv[1],"-w")) {
		int retVal = hasWriteEnd(argv[2]);
		
		printf("Write end: %s\n", retVal == 1 ? "Yes" : "No");
	}
	else {
		check_error(0, "wrong option");
	}
	
	exit(EXIT_SUCCESS);
}

/* funkcija proverava da li je neki drugi proces otvorio pajp u R modu */
int hasReadEnd(const char* path) {
	
	/* da bismo to postigli, nas proces treba da otvori pajp u WR modu 
	 * uz dodatak O_NONBLOCK flaga da bi poziv odmah pukao u slucaju blokiranja 
	 */
	int fd = open(path, O_WRONLY | O_NONBLOCK);
	
	/* ako je poziv pukao */
	if (fd == -1) {
		
		/* zbog toga sto niko nije otvorio fifo u r modu */
		if (errno == ENXIO) {
			/* vracamo 0 kao signal da pajp nije otvoren */
			return 0;
		}
		else {
			/* ako je nesto drugo razlog pucanja, prekidamo program */
			check_error(0, "open failed");
		}
	}
	
	/* u suprotnom zatvaramo fajl */
	close(fd);
	
	/* vracamo 1 kao signal da je pajp otvoren */
	return 1;
}

/* funkcija proverava da li je neki drugi proces otvorio pajp u R modu */
int hasWriteEnd(const char* path) {
	
	/* da bismo to postigli otvaramo fajl u R modu uz isto objasnjenje kao gore */
	int fd = open(path, O_RDONLY | O_NONBLOCK);
	/* otvaranje fajl u r modu, samo po sebi nije blokirajuca operacija, pa 
	 * proveravamo poziv na uobicajen nacin */
	check_error(fd != -1, "open failed");
	
	/* citanje je ustvari blokirajuca operacija, pa na taj nacin testiramo da li je fajl
	 * otvoren ili ne
	 */
	
	/* pokusamo da ucitamo samo jedan karakter */
	char c;
	int retVal = read(fd, &c, 1);
	
	/* ako ucitamo EOF, to je ok, jer to znaci da niko nije otvorio fajl */
	if (retVal == 0) {
		/* zatvorimo fajl i vratimo odgovarajucu vrednost */
		close(fd);
		return 0;
	}
	/* ako je read pukao */
	else if (retVal < 0) {
		
		/* i razlog je blokiranje */
		if (errno == EAGAIN) {
			/* to znaci da je neko otvorio fajl, ali da nista nije upisao
			 * pa zatvarmao fajl i vracamo odgovarajucu vrednost 
			 */
			close(fd);
			return 1;
		}
		else {
			/* ako je bilo sta drugo uzrok pucanja, prekidamo program */
			check_error(0, "read failed");
		}
	}
	else {
		/* ako smo ucitali karakter, neko je otvorio fajl i nesto upisao, 
		 * pa samo zatvaramo fajl i vracamo odgovarajucu vrednost.
		 */
		close(fd);
		return 1;
	}
	
}


			
