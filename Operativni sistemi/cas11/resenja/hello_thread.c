	/* program ilustruje kreiranje niti */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <errno.h>
#include <pthread.h>
#include <math.h>

#define check_error(expr, userMsg)\
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while(0)

/* makro za obradu greska kod pthread funkcija
 * BITNO:
 * pthread funkcije ne postavljaju errno, vec kao povratnu vrednost vracaju
 * kod greske, tj. odgovarajuci broj greske. 
 * 
 * S obzirom da se radi o konkurentnom programu, pristup i promena vrednosti
 * errno-a se ustvari razmotavaju u poziv sinhronizovanoj funkciji, sto je izuzetno
 * skupa operacija. 
 * 
 * Ocekivano je da pozivi u velikom broju uspevaju, pa promena vrednosti errno-a
 * ima smisla samo onda kada se dogodi greska, tj. kada povratna vrednost nije 0. 
 * Postavljanje errno-a iznova i iznova na 0, tj. SUCCESS je besmisleno skupa i 
 * nepotrebna operacija. Zbog toga u makrou postoji provera if (_pthreadErr)
 * i ako je povratna vrednost razlicita od nule, to je bas errno
 * koji treba da postavimo rucno, nakon cega ide prekid programa na uobicajen nacin.
 */ 
#define check_errorThread(pthreadErr, userMsg)\
	do {\
		int _pthreadErr = pthreadErr; \
		if (_pthreadErr) { \
			errno = _pthreadErr; \
			check_error(false, userMsg); \
		} \
	} while(0)

/* tip argumenta funkcije koja implementira nit */
typedef struct {
	int threadNo;
} inputArg;

/* povratni tip funkcije koja implementira nit */
typedef struct {
	double num;
} outputArg;

/* implementacija niti */
void* threadFunc(void* arg) {
	
	/* ulazni argument kastujemo u odgovarajuci tip */
	inputArg* threadArg = (inputArg*) arg;
	/* dinamicki alociramo mesto za povratnu vrednost iz funkcije */
	outputArg* retVal = malloc(sizeof(outputArg));
	check_error(retVal != NULL, "...");
	
	/* stampamo poruku korisniku */
	printf("Thread number: %d\n", threadArg->threadNo);
	
	/* inicijalizujemo povratnu vrednost funkcije */
	retVal->num = sqrt(threadArg->threadNo);
	
	/* vracamo rezultat izvrsavanja funkcije 
	 * BITNO:
	 * exit() u bilo kom tredu prekida citav program.
	 * Za prekidanje pojedinacnih tredova korisiti return ili pthread_exit();
	 */
	return retVal;
}

int main(int argc, char** argv) {
	
	check_error(argc == 2,"...");
	
	/* alociramo prostor za thread ID-ove 
	 * BITNO:
	 * nema recikliranja ID-eva. Svaki tred mora da ima odvojen prostor
	 * za svoj id.
	 */
	int numThreads = atoi(argv[1]);
	pthread_t* tids = malloc(numThreads*sizeof(pthread_t));
	check_error(tids != NULL, "...");
	
	/* alociramo prostor za argumente tredova 
	 * BITNO:
	 * vazi ista prica kao za ID-eva. Svaki tred mora da ima odvojen prostor
	 * za svoj argument
	 */
	inputArg* args = malloc(numThreads*sizeof(inputArg));
	check_error(args != NULL, "...");
	
	/* startujemo tredove */
	int i=0;
	for (i=0; i < numThreads; i++) {
		
		args[i].threadNo = i + 1;
		check_errorThread(pthread_create(&tids[i], NULL, threadFunc, &args[i]), "...");
	}
	
	/* cekamo da se svi tredovi zavrse */
	for (i = 0; i < numThreads; i++) {
		/* pokazivac na odgovarajuci tip podataka u koji ce nam 
		 * funkcija pthread_join upisati adresu povratne vrednosti
		 * iz niti 
		 */ 
		outputArg* retVal = NULL;
		check_errorThread(pthread_join(tids[i], (void**)&retVal), "...");
		printf("Thread finished: %.2lf\n", retVal->num);
		
		/* oslobadjamo resurse
		 * 
		 * BITNO:
		 * ovo je izuzetno osetljivo mesto na kome memorija moze lako da curi.
		 * Svaki pokrenuti tred dinamicki alocira prostor za svoju povratnu vrednost,
		 * sto znaci da moramo rucno da oslobodimo svaku povratnu vrednost koju uhvatimo. 
		 * 
		 * Kada radite sa tredovima, pazljivo vodite racuna o memoriji.
		 */ 
		free(retVal);
	}
	
	/* oslobadjamo resurse */
	free(tids);
	free(args);
		
	exit(EXIT_SUCCESS);
}
