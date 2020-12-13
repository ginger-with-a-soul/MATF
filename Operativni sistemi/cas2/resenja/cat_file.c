/* Program nadovezuje sadrzaj fajla na standardni izlaz 
 *
 * Primer poziva:
 * ./cat_file test.txt
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (1024)

int main(int argc, char** argv) {
	
	/* provera broja argumenata */
	if (argc != 2) {
		fprintf(stderr, "./catfile path");
		exit(EXIT_FAILURE);
	}
	
	/* otvaramo fajl u read modu 
	 * i proveravamo greske
	 */
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open failed");
		exit(EXIT_FAILURE);
	}
	
	/* staticka ili dinamicka alokacija - nebitno
	 * logika kopiranja je bitna 
	 *
	 * ovde je iskoriscena dinamicka alokacija
	 * uz obaveznu obradu gresaka
	 */
	char* buf = malloc(MAX_SIZE);
	if (buf == NULL)
		exit(EXIT_FAILURE);
	
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
	while ((bytesRead = 
			read(fd, buf, MAX_SIZE)) > 0) {
		
		/* u slucaju da hocu da prikazem procitamo pomocu std biblioteke
		 * moram da terminiram string eksplicitno
		 *
		 * read funkcija radi na nivou bajtova i nikada ne terminise string automatski
		 * 
		 * bez eksplicitne terminacija, pored eljenog sadrzaja odstampalo bi se i djubre iz 
		 * bafera koje ne pripada trenutnom pozivu
		 */
		//buf[bytesRead] = 0;
		//fprintf(stdout, "%s\n", buf);
		
		/* procitani sadrzaj stampam na standardni izlaz
		 * Uvek se koriste makroi STDOUT_FILENO i ostali, a nikada brojevi 0,1,2
		 *
		 * Druga bitna stvar je da uvek ispisete onoliko koliko ste procitali, dakle bytesRead,
		 * a ne sadrzaj celog bafera.
		 *
		 * provera gresaka je obavezna
		 */
		if (write(STDOUT_FILENO, 
				buf, bytesRead) != bytesRead){
			
			fprintf(stderr, "write failed\n");
			exit(EXIT_FAILURE);
		}
	}
	
	/* nakon iskakanja iz petlje, neophodna je proveriti da li je razlog izlaska EOF
	 * ili greska
	 * ako je bytesRead == -1, onda se radi o grasci
	 */
	if (bytesRead == -1) {
		
		fprintf(stderr, "read failed\n");
		exit(EXIT_FAILURE);
	}
	
	/* obavezno oslobadjanje koriscenih resursa */
	free(buf);
	close(fd);
	
	/* zavrsvanje sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}
