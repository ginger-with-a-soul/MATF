/* Program pokusava da kreira direktorijum na putanji koju korisnik
 * sa pravima pristupa koje bi korisnik zeleo.
 * Putanja i prava pristupa se prosledjuje kao argumenti
 * komandne linije.
 *
 * Primer poziva:
 * ./mkdir dir1 0777
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	/* provera broja argumenata */
	if (argc != 3) {
		fprintf(stderr, "./2 dirPath privileges");
		exit(EXIT_FAILURE);
	}
	
	/* konvertovanje broja iz stringa u osnovi 8
	 * u long
	 */
	long mode = strtol(argv[2], NULL, 8);
	
	/* pokusavamo da napravimo direktorijum na putanji sa zeljenim
	 * pravima pristupa uz neophodno proveru gresaka
	 *
	 * BITNO:
	 * drugi argument mkdir poziva je samo nasa zelja, koja ne mora da 
	 * nam se ostvari. konacna prava pristupa zavise od umaska
	 */
	if (mkdir(argv[1], mode) == -1){
		fprintf(stderr, "mkdir faiiled\n");
		exit(EXIT_FAILURE);
	}
	
	/* zavrsvanje sa odgovarajucim statusom */
	exit(EXIT_FAILURE);
}
