#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define check_error(expr, userMsg) \
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while (0)

/* mapiramo dane u nedelji sa brojevima koji im odgovaraju u srukturi tm */
char* week[7] = {"Nedelja", "Ponedeljak", "Utorak", "Sreda", "Cetvrtak", "Petak", "Subota"};

int main(int argc, char** argv) {
	
	/* provera argumenata */
	check_error(argc==2, "./1 noOfDays");
	
	/* konverzija argumenta u broj */
	int days = atoi(argv[1]);
	
	/* citamo trenutno vreme */
	time_t now = time(NULL);
	/* pomeramo datume za onoliko dana koliko korisnik zeli */
	now += days*24*60*60;
	
	/* razbijamo vreme na citljiv format */
	struct tm* brokenTime = localtime(&now);
	check_error(brokenTime != NULL, "...");
	
	/* stampamo dan u nedelji na srpskom */
	printf("%s\n", week[brokenTime->tm_wday]);
	
	exit(EXIT_SUCCESS);
}
