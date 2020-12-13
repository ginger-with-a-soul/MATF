/* program ilustruje zakljucavanje fajlova */
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
	
	check_error(argc == 6, "...");
	
	char* fpath = argv[1];			/* putanja do fajla */
	int start = atoi(argv[2]);		/* pocetak regiona koji zakljucavamo */
	int length = atoi(argv[3]);		/* duzina koju zakljucavamo */
	int sleepTime = atoi(argv[4]);	/* vreme koliko drzimo katanac */
	int lockType = argv[5][0] == 'r' ? F_RDLCK : F_WRLCK;	/* tip katanca */
	
	/* otvaramo fajl u RDWR modu
	 * vodite racuna da se mod poklapa sa onim sto zelite da radite fajla i katancima koje postavljate 
	 */
	int fd = open(fpath, O_RDWR);
	check_error(fd != -1, "open failed");
	
	/* zakljucavamo region definisan argumentama komandne linije
	 * prvo inicijalizujemo strutkuru flock
	 *
	 * BITNO:
	 * obratiti posebnu paznju ako koristite stream-ove.
	 */
	struct flock lock;
	lock.l_type = lockType;
	lock.l_whence = SEEK_SET;
	lock.l_start = start;
	lock.l_len = length;
	
	/* pomocu fcntl pokusamo da zakljucamo region */
	printf("Zakljucavanje...\n");
	check_error(fcntl(fd, F_SETLK, &lock) != -1, "fcntl failed");
	
	/* ako uspe, drzimo katanac odredjeno vreme */
	printf("Zakljucao\n");
	sleep(sleepTime);
	
	/* otkljucamo region */
	lock.l_type = F_UNLCK;
	check_error(fcntl(fd, F_SETLK, &lock) != -1, "lock failed");
	
	/* zatvorimo fajl deskriptor */
	printf("Otkljucao\n");
	close(fd);
		
	exit(EXIT_SUCCESS);
}
			
