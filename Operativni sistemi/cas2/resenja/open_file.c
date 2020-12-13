/* Program otvara fajl u modu koji zeli korisnik.
 * Putanja do fajla i zeljeni mod se prosledjuju kao 
 * argumenti komandne linije.
 *
 * Primer poziva:
 * ./open_file test.txt r+ 
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

/* funkcija klonira fopen poziv, samo koristi file deskriptore 
 * arg1: putanja do fajla
 * arg2: mod u kome treba otvoriti fajl
 * ret:  fajl deskriptor pridruzen fajlu
 */
int my_fopen(const char* path, const char* mode);

int main(int argc, char** argv) {
	
	/* provera broja argumenata */
	if (argc != 3) {
		fprintf(stderr, "./1 filePath fmode\n");
		exit(EXIT_FAILURE);
	}
	
	/* otvaranje fajla u modu koji je izabrao korisnik */
	int fd = my_fopen(argv[1], argv[2]);
	
	/* zatvaranje fajla 
	 * neophodno da ne bi doslo do curenja fajl deskriptora 
	 */
	close(fd);
	
	/* zavrsvanje sa odgovarajucim statusom */
	exit(EXIT_SUCCESS);
}

/* funkcija klonira fopen poziv, samo koristi file deskriptore 
 * arg1: putanja do fajla
 * arg2: mod u kome treba otvoriti fajl
 * ret:  fajl deskriptor pridruzen fajlu
 */
int my_fopen(const char* path, const char* mode) {
	
	/* prava pristupa sa kojim zelimo da kreiramo fajl 
	 * u slucaju da se radi o "w" ili "a" modu
	 *
	 * BITNO:
	 * treci argument funkcije open je samo nasa zelja i nista vise
	 * da li ce fajl zaista biti kreiran sa tim pravima pristupa odlucuje umask
	 */
	static mode_t fmode = 0777;
	
	/* promenljiva pomocu koje cemo definisati flagove u zavisnosti
	 * od korisnikove zelje
	 *
	 * mod |	prava pristupa
	 * -------------------------------------------
	 * r   | O_RDONLY
	 * -------------------------------------------
	 * r+  | O_RDWR
	 * -------------------------------------------
	 * w   | O_WRONLY | O_TRUNC | O_CREAT
	 * -------------------------------------------
	 * w+  | O_RDWR | O_TRUNC | O_CREAT
	 * -------------------------------------------
	 * a   | O_WRONLY | O_APPEND | O_CREAT
	 * -------------------------------------------
	 * a+  | O_RDWR | O_APPEND | O_CREAT
	 * -------------------------------------------
	 *
	 * Detalji o modovima P1 i P2 i TLPI
	 * Posebno obratiti paznju na razlike izmedju r+, w+ i a+ modova
	 */
	int flags = 0;
	switch (mode[0]) {
		
		case 'r':
			flags |= mode[1] == '+' ? 
						O_RDWR : O_RDONLY;
			break;
		case 'w':
			flags |= mode[1] == '+' ? 
						O_RDWR : O_WRONLY;
			flags |= O_TRUNC;
			flags |= O_CREAT;
			break;
		case 'a':
			flags |= mode[1] == '+' ? 
						O_RDWR : O_WRONLY;
			flags |= O_APPEND;
			flags |= O_CREAT;
			break;
		default:
			fprintf(stderr, "Wrong mode\n");
			exit(EXIT_FAILURE);
			break;
	}
	
	
	/* otvaramo fajl */
	int fd = open(path, flags, fmode);
	/* obavezna provera gresaka - minimalni pristup */
	if (fd == -1) {
		fprintf(stderr, "file open failed\n");
		exit(EXIT_FAILURE);
	}
	/* vracamo otvoreni fd pomocu return mehanizma */
	return fd;
}
