/* Program ilustruje upotrebu sistemskog poziva lseek 
 * i pozicioniranje fajl ofseta.
 * 
 * Primer poziva:
 * ./file_size.c test.txt
 *
 * BITNO:
 * Posledica pozicioniranja fajl ofseta na kraj je da 
 * cemo saznati kolika je velicina fajla. Ali to nije cilj
 * zadatka!
 *
 * JOS BITNIJE:
 * Ovako se ne ispituje velicina fajla. Nikada!!!
 * Za to se koristi sistemski poziv stat.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char** argv) {
	
	/* provera broja argumenata */
	if (argc != 2) {
		
		fprintf(stderr, "./file_size path\n");
		exit(EXIT_FAILURE);
	}
	
	/* otvaramo fajl u r modu, jer nema potrebe da menjamo
	 * njegov sadrzaj i obavezno proveramo greske 
	 */
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "file open failed\n");
		exit(EXIT_FAILURE);
	}
	
	/* pozicioniramo se na kraj fajla */
	off_t fsize = lseek(fd, 0, SEEK_END);
	
	/* provera gresaka */
	if (fsize == (off_t)-1) {
		fprintf(stderr, "lseek failed\n");
		exit(EXIT_FAILURE);
	}
	
	/* i na kraju stampamo koliko smo udaljeni od pocetka fajla
	 * S obzirom da smo se pozicionirali na kraj fajla, ovaj broj
	 * ce biti ekvivalentan velicini fajla.
	 */
	printf("File size: %jdB\n", (intmax_t)fsize);
	
	/* zatvaramo fajl */
	close(fd);
	
	/* zavrsvanje sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}
