/* program ilustruje precizno merenje vremena na sistemu 
 * 
 * Na sistemu se definisana tri tipa vremena:
 * 1. wall clock time -> vreme koje odgovara ukupnom protoku vremena
 * 						 od pokretanja aplikacije do njenog zavrsetka, tj.
 * 						 odgovara vremenu koje bi izmerila stoperica.
 * 						 Posledica ovoga je da je u ovo vreme ukljuceno i
 * 						 ono vreme koje je program proveo blokiran.
 * 2. user time	-> Vreme koje je program proveo u korisnickom rezimu. 
 * 				   Ukljucuje samo vreme koje program fizicki provede koristeci
 * 				   procesor.
 * 3. system time -> Vreme koje je program proveo u sistemskom rezimu.
 * 					 Ukljucuje samo vreme koje program fizicki provede koristeci
 * 				     procesor.
 * Za detalje TLPI.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <string.h>

#define check_error(expr,userMsg) \
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while (0)

#define MAX_SIZE (1024)

/* tip podataka koji opisuje stopericu */
typedef struct {
	
	struct timeval wallTime; /* wall clock time  */
	struct timeval userTime; /* korisnicko vreme */
	struct timeval sysTime;	 /* sistemsko vreme */
} stopwatch_t;

/* funkcija "pokrece" stopericu,
 * tj. pamti trenutno vreme na sistemu 
 */ 
void start(stopwatch_t *s) {
	
	/* citamo precizno vreme pomocu gettime of day */
	check_error(gettimeofday(&(s->wallTime), NULL) != -1, "...");
	
	/* da bismo dobili korisnicko i sistemsko vreme moramo da pozovemo
	 * sistemski poziv getrusage, jer oba ova vremena spadaju u resurse
	 * sistema
	 */ 
	struct rusage r;
	check_error(getrusage(RUSAGE_SELF, &r) != -1, "...");
	
	/* kopiramo vremena u odgovarajuce strukture */
	memcpy(&(s->userTime),&(r.ru_utime), sizeof(struct timeval));
	memcpy(&(s->sysTime),&(r.ru_stime), sizeof(struct timeval));
}

/* funkcija izracunava razliku dva vremena
 * i rezultat upisuje u drugi argument
 */ 
void diff(stopwatch_t* a, stopwatch_t *b) {
	
	intmax_t diffInUsec = (a->wallTime.tv_sec*1000000 - b->wallTime.tv_sec*1000000) + (a->wallTime.tv_usec - b->wallTime.tv_usec);
	b->wallTime.tv_sec = diffInUsec/1000000;
	b->wallTime.tv_usec= diffInUsec%1000000;
	
	diffInUsec = (a->userTime.tv_sec*1000000 - b->userTime.tv_sec*1000000) + (a->userTime.tv_usec - b->userTime.tv_usec);
	b->userTime.tv_sec = diffInUsec/1000000;
	b->userTime.tv_usec= diffInUsec%1000000;
	
	diffInUsec = (a->sysTime.tv_sec*1000000 - b->sysTime.tv_sec*1000000) + (a->sysTime.tv_usec - b->sysTime.tv_usec);
	b->sysTime.tv_sec = diffInUsec/1000000;
	b->sysTime.tv_usec= diffInUsec%1000000;
}

/* funkcija zaustavlja stopericu i izracunava proteklo vreme */
void stop(stopwatch_t* s) {
	
	/* hvatamo trenutno vreme, startnovanjem nove stoperice */
	stopwatch_t now;
	start(&now);
	/* izracunavamo proteklo vreme */
	diff(&now, s);
}

void print_time(stopwatch_t* s){
	
	printf("Wall: %ds %dus\n", (int)(s->wallTime.tv_sec), (int)(s->wallTime.tv_usec));
	printf("User: %ds %dus\n", (int)(s->userTime.tv_sec), (int)(s->userTime.tv_usec));
	printf("Sys: %ds %dus\n", (int)(s->sysTime.tv_sec), (int)(s->sysTime.tv_usec));
}

int main(int argc, char** argv) {
		
	stopwatch_t s;
	int fd = 0;
	
	start(&s);
	fd = open("/dev/urandom", O_RDONLY);
	check_error(fd != -1, "...");
	char buffer[MAX_SIZE];
	for (int i = 0; i < 100000; i++) {
		int retVal = read(fd, buffer, MAX_SIZE);
		check_error(retVal != -1, "...");
	}
	close(fd);
	stop(&s);
	
	print_time(&s);
	
	start(&s);
	double ss = 0;
	double k = 0;
	for (int i = 0; i < 10000; i++) {
		ss+=250*k+3848;
		k*=(ss-384)*989;
		ss+=k;
	}
	stop(&s);
	
	print_time(&s);
	
	exit(EXIT_SUCCESS);
}
