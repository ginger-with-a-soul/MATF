/* Program brise sadrzaj fajla uz sakrivanje tragova.
 *
 * Primer poziva:
 * ./truncate test.txt
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <utime.h>

/* makro za obradu gresaka -> da ne bih stalno kucao if(...) */
#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			fprintf(stderr, "%s\n", userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)
	
int main(int argc, char** argv) {
	
	/* provera broja argumenata */
	check_error(argc == 2, "./userInfo userName");
	
	/* pamtimo informacije o fajlu pre otvaranja */
	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) != -1, "stat failed");
	
	/* otvaramoa fajl u modu za pisanje
	 * dakle, menjamo mu i vreme pristupa i vreme modifikacije */
	FILE* f = fopen(argv[1], "w");
	check_error(f != NULL, "file open failed");
	/* zatvaramo fajl */
	fclose(f);
	
	/* stara vremena pristupa i modifikacije upisujemo u strukturu utimbuf */
	struct utimbuf vremena;
	vremena.actime = fInfo.st_atime;
	vremena.modtime = fInfo.st_mtime;
	
	/* pomocu sist poziva utime "sakrivamo" brisanje fajla, tako sto
	 * vratimo stara vremena pristupa koja smo zapamtili pomocu stat poziva
	 * / 
	check_error(utime(argv[1], &vremena) != -1, "utime failed");
	
	/* zavrsavanje sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}
