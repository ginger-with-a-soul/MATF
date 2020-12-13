/* Program kopira fajl sa mesta A na mesto B.
 * Putanje se prosledjuju kao argumenti komandne linije
 *
 * Primer poziva:
 * ./cp_file srcFile destFile
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (1024)

/* makro za obradu gresaka - da ne bih stalno kucao if (...) */
#define check_error(expr, msg) \
	do { \
		if (!(expr)) {\
			fprintf(stderr, "%s\n", msg);\
			exit(EXIT_FAILURE); \
		}\
	} while (0)

int main(int argc, char** argv) {
	
	/* provera broja argumenata */
	check_error(argc == 3, "./cpfile srcPath destPath\n");
	
	/* src file otvaramo u modu za citanje */
	int srcFd = open(argv[1], O_RDONLY);
	check_error(srcFd != -1, "open failed");
	/* dest file otvaramo u modu za pisanje */
	int destFd = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, 0644);
	check_error(destFd != -1, "open failed");
	
	/* staticka ili dinamicka alokacija - nebitno
	 * logika kopiranja je bitna 
	 *
	 * ovde je iskoriscena dinamicka alokacija
	 * uz obaveznu obradu gresaka
	 */
	char* buf = malloc(MAX_SIZE);//[MAX_SIZE];
	check_error(buf != NULL, "malloc failed");
	
	/* promenljiva koja nam kaze koliko smo bajtova procitali */
	int bytesRead = 0;
	
	/* citanje kompletnog fajla se ne vrsi jednim read pozivom
	 * vec je logika ista kao u P2 -> citam sve dok ne udarim u EOF
	 *
	 * read sistemski poziv vraca 0 kada udari u EOF ili -1 ako se desila
	 * greska.
	 *
	 * Dakle, u petlji citam sve dok mi je povratna vrednost funkcije veca od 0
	 */
	while ((bytesRead = read(srcFd, buf, MAX_SIZE)) > 0) {
		
		/* procitani sadrzaj stampam na dest file
		 *
		 * Druga bitna stvar je da uvek ispisete onoliko koliko ste procitali, dakle bytesRead,
		 * a ne sadrzaj celog bafera.
		 *
		 * provera gresaka je obavezna
		 */
		check_error(write(destFd, buf, bytesRead) == bytesRead, "write faiiled");
	}
	
	/* nakon iskakanja iz petlje, neophodna je proveriti da li je razlog izlaska EOF
	 * ili greska
	 * ako je bytesRead == -1, onda se radi o grasci
	 */
	check_error(bytesRead != -1, "read failed");
	
	/* obavezno oslobadjanje koriscenih resursa */
	free(buf);
	close(srcFd);
	close(destFd);
	
	/* zavrsvanje sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}
