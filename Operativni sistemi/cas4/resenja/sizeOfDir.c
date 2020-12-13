/* Program obilazi direktorijum i racuna njegove velicinu
 *
 * Primer poziva:
 * ./sizeOfDir dirPath
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <errno.h>
#include <dirent.h>

#include <string.h>

/* makro za proveru gresaka */
#define check_error(expr, userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)

/* funkcija rekurzivno obilazi direktorijum i racuna njegovu velicinu
 *
 * arg1: trenutna putanja
 * arg2: pokazivac na promenljivu u kojoj cuvamo tekucu velicinu direktorijuma
 */
bool traverseDir(char* path, unsigned* dirSize);

int main(int argc, char** argv) {
	
	/* provera broja argumenata */
	check_error(argc == 2, "./sizeOfDir path");
	
	/* proveravamo da li je argument direktorijum */
	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) != -1, "stat failed");
	check_error(S_ISDIR(fInfo.st_mode), "not a dir");
	
	/* i ako jeste, obilazimo ga i racunamo njegovu velicinu */
	unsigned dirSize = 0;
	check_error(traverseDir(argv[1], &dirSize), "dir traversal failed");
	
	/* stampamo velicinu koju smo izracunali */
	printf("Dir size: %u\n", dirSize);
	
	/* zavrsavamo program sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}

/* funkcija rekurzivno obilazi direktorijum i racuna njegovu velicinu
 *
 * arg1: trenutna putanja
 * arg2: pokazivac na promenljivu u kojoj cuvamo tekucu velicinu direktorijuma
 */
bool traverseDir(char* path, unsigned* dirSize) {
	
	/* citamo informacije o trenutnom fajlu */
	struct stat fInfo;
	if (lstat(path, &fInfo) == -1) {
		
		return false;
	}
	
	/* dodajemo velicinu fajla na tekuci zbir */
	*dirSize += fInfo.st_size;
	
	/* ukoliko se ne radi o direktorijumu */
	if (!S_ISDIR(fInfo.st_mode)) {
		
		/* prekidamo rekurziju */
		return true;
	}
	
	/* ako je u pitanju dirketorijum, otvaramo ga */
	DIR* dir = opendir(path);
	if (dir == NULL) {
		return false;
	}
	
	/* u petlji citamo sadrzaj direktorijuma */
	struct dirent* currEntry;
	while ((currEntry = readdir(dir)) != NULL) {
		
		/* u svakom trenutku treba da budemo svesni svog trenutnog radnog direktorijuma (pwd)
		 * pwd nam je u svakom trenutku ona putanja koju nam je korisnik prosledio na pocetku programa,
		 * pa u svakom trenutku moramo rucno da pravimo putanje do svih drugih fajlova koje srecemo u
		 * obilasku
		 *
		 * na nasu tekucu putanju, moramo da dodamo "/" trenutno ima fajla iz direktorijuma koji smo otvorili
		 * i terminirajucu nulu 
		 */
		
		/* dinamicki alociramo prostor za novu putanju */
		char* newPath = malloc(strlen(path) + 1 + strlen(currEntry->d_name) + 1);
		check_error(newPath != NULL, "malloc failed");
		
		/* formiramo putanju na gore opisani nacin */
		strcpy(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, currEntry->d_name);
		
		/* u slucaju da se radi o "." ili ".." direktorijumima, moramo da ih preskocimo,
		 * jer u suprotnom upadamo u beskoacnu rekurziju
		 */ 
		if (!strcmp(currEntry->d_name, ".") || !strcmp(currEntry->d_name, "..")){
			
			/* iako ih preskacemo, to ne znaci da treba da ih iskljucimo iz razmatranja */
			
			/* citamo informacije o fajlu */
			if (stat(newPath, &fInfo) == -1) {
				
				/* ako poziv pukne, oslobadjamo memoriju */
				free(newPath);
				/* i vracamo signal za gresku kroz celo rekurzivno stablo */
				return false;
			}		
			
			/* u suprotnom dodajemo velicinu fajla na tekuci zbir */
			*dirSize += fInfo.st_size;
			/* oslobadjamo memoriju */
			free(newPath);
			/* i prelazimo na sledeci fajl u direktorijumu */
			continue;
		}
		
		/* ako se ne radi o "." i ".." , rekurzivno pozivamo funkciju i obradjujemo fajl */
		bool state = traverseDir(newPath, dirSize);
		/* oslobadjamo memoriju */
		free(newPath);
		
		/* ako se desila greska u obilasku */
		if (state == false)
			/* propagiramo je dalje kroz rekurzivno stablo */
			return false;
	}
	
	/* zatvaramo direktorijum */
	if (closedir(dir) == -1)
		return  false;
	
	/* povratnu vrednost tekuceg rekurzivnog poziva postavljamo na uspeh */
	return true;
}
