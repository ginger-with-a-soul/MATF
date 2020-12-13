/* program ilustruje sinhronizaciju niti pomocu muteksa 
 * Program racuna ukupan zbir brojeva koji se nalaze u fajlovima cije se 
 * putanje prosledjuju kao arguemnti komandne linije.
 * Za svaki fajl se otvara po jedan tred koji racuna lokalnu sumu brojeva
 * u tom fajlu. Nakon izracunavanja lokalne sume uvecava se globalna suma.
 * Ocigledno globalna suma je deljena promenljiva i treba je sinhronizovati.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <errno.h>
#include <pthread.h>

#define check_error(expr, userMsg)\
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while(0)

#define check_errorThread(pthreadErr, userMsg)\
	do {\
		int _pthreadErr = pthreadErr; \
		if (_pthreadErr) { \
			errno = _pthreadErr; \
			check_error(false, userMsg); \
		} \
	} while(0)

/* globalna suma i mutex */
int globalSum = 0;
pthread_mutex_t globalLock;// = PTHREAD_MUTEX_INITIALIZER;


/* funkcija implementira nit */
void* threadFunc(void* arg) {
	
	/* otvaranje fajla */
	char* filePath = arg;
	FILE* f = fopen(filePath, "r");
	check_error(f != NULL, "...");
	
	/* cesta greska koja dovodi do ponistavanja potrebe za nitima
	 * zakljucavanje cele funkcije svodi program na klasicni sekvencijalni, samo sporiji. 
	 * 
	 * BITNO:
	 * Nikada se ne zakljucava cela funkcija
	 * vec samo deljeni resurs
	 */ 
	//check_errorThread(pthread_mutex_lock(&globalLock), "...");
	
	/* racunanje zbira brojeva u fajlu */ 
	int localSum = 0, x = 0;
	
	while(fscanf(f, "%d", &x) == 1) {
		localSum += x;
	}
	
	/* provera gresaka */
	check_error(feof(f), "...");
	
	/* sinhronizovano uvecavanje globalne sume */
	check_errorThread(pthread_mutex_lock(&globalLock), "...");
	globalSum += localSum;
	check_errorThread(pthread_mutex_unlock(&globalLock), "....");
	
	/* zatvaranje fajla */
	fclose(f);
	return NULL;
}

int main(int argc, char** argv) {
	
	check_error(argc > 1, "...");
	int numT = argc - 1;
	
	/* alokacija prostora za ID-eve */
	pthread_t* tids = malloc(sizeof(pthread_t)*numT);
	check_error(tids != NULL, "....");
	
	/* inicjalizovanje muteksa 
	 * 
	 * BITNO:
	 * ne sme da se preskoci. 
	 */
	check_errorThread(pthread_mutex_init(&globalLock, NULL), "...");
	
	/* startovanje tredova */
	for (int i = 0; i<numT; i++) {
		
		check_errorThread(pthread_create(&tids[i], NULL, threadFunc, argv[i+1]), "....");
	}
	
	/* cekanje da se tredovi zavrse */
	for (int i=0; i<numT; i++) {
		
		check_errorThread(pthread_join(tids[i], NULL), "...");
	}
	
	/* stampanje rezultata */
	printf("Total sum: %d\n", globalSum);
	
	/* oslobadjanje resursa */
	free(tids);
	check_errorThread(pthread_mutex_destroy(&globalLock), "...");
	
	exit(EXIT_SUCCESS);
}
