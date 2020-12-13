/* Program ilustruje upotrebu i kontrolu izvrsavanja pomocu
 * uslovnih promenljivih.. 
 * Main tred ucitava nizove sa standardnog ulaza i signaliziranjem 
 * uslovnoj promenljivoj pusta samo jedan tred iz reda blokiranih koji
 * obradjuje ucitane podatke
 * 
 * BITNO:
 * zbog preglednosti je izbacena obrada gresaka kod pthread poziva
 * To se nece tolerisati na ispitu.
 */ 
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

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

#define MAX_SIZE (100)

/* deljene promenljive */
int globalDataCount = 0;
int globalArray[MAX_SIZE];
/* sinhronizacioni mehanizam */
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t globalSignaler = PTHREAD_COND_INITIALIZER;

/* funkcija implementira tred */
void* threadFunc(void* arg) {
	
	/* primitivne tipove uvek saljite na ovaj nacin
	 * na 64bit sistemu odsecanje zavisi od "endianness"
	 * i ne mozete da budete sigurni da li ce klasicna pesacka
	 * konverzija pokazivaca sa &x i *(int*)arg odseci ispravan deo
	 * pokazivaca. pokazivac je 8 bajtova, a int je 4, pa postoje cetiri moguce
	 * kombinacije
	 * 
	 * koriscenjem intptr_t tipa, izbegavate citavu ovu gimnastiku i dobicete
	 * ispravne rezultate svaki put. 
	 */ 
	int ID = (int)(intptr_t)arg;
	
	/* tred se vrti u petlji */
	while (1) {
		
		/* zakljucava kriticni region */
		pthread_mutex_lock(&globalLock);
		/* proverava da li treba da racuna nesto */
		while (globalDataCount == 0) {
			/* dok god ne treba, blokira se na uslovnoj promenljivoj */
			pthread_cond_wait(&globalSignaler, &globalLock);
		}
		
		/* kada je njegov red, proverava da li treba da prekine izvrsavanje */
		if (globalDataCount == -1) {
			/* ako treba, prepusta muteks drugima */
			pthread_mutex_unlock(&globalLock);
			/* i iskace iz petlje */
			break;
		}
		
		/* stampa svoj id i rezultat izvrsavanja */
		printf("Thread: %d\n", ID);
		for (int i = 0; i < globalDataCount; i++)
			printf("%d ", globalArray[i]*globalArray[i]);
			
		printf("\n");
		
		/* resetuje flag */
		globalDataCount = 0;
		
		/* otkljucava muteks */
		pthread_mutex_unlock(&globalLock);
	}
	
	printf("Thread exited: %d\n", ID);
	
	return NULL;
}

int main(int argc, char** argv) {
	
	check_error(argc == 2,"...");
	
	/* alociramo prostor za tredove */
	int numT = atoi(argv[1]);
	pthread_t* tids = malloc(sizeof(pthread_t)*numT);
	check_error(tids != NULL, "...");
	
	/* startujemo onoliko tredova koliko zeli korisnik */
	for (int i = 0; i < numT; i++) {
		
		check_errorThread(pthread_create(&tids[i], NULL, threadFunc, (void*)(intptr_t)i), "...");
	}
	
	char* line = NULL;
	size_t lineLen = 0;
	
	/* u petlji ucitavamo liniju po liniju sa ulaza */
	while (getline(&line, &lineLen, stdin) != -1) { 
		
		int bytesRead = 0;
		int totalBytes = 0;
		
		/* zakljucavamo kriticnu sekciju */
		pthread_mutex_lock(&globalLock);
		
		/* citamo broj brojeva na ulazu */
		sscanf(line, "%d%n", &globalDataCount, &bytesRead);
		totalBytes += bytesRead;
		
		/* ako je minus jedan */
		if (globalDataCount == -1) {
			
			/* otkljucavamo muteks */
			pthread_mutex_unlock(&globalLock);
			/* budimo sve tredove */
			pthread_cond_broadcast(&globalSignaler);
			/* iskacemo iz petlje */
			break;
		}
		
		/* u petlji ucitavamo niz brojeva */
		for (int i = 0; i < globalDataCount; i++) {
			
			sscanf(line + totalBytes, "%d%n", &globalArray[i], &bytesRead);
			totalBytes += bytesRead;
		}
		
		/* otkljucavamo kriticnu sekciju */
		pthread_mutex_unlock(&globalLock);
		/* budimo samo jedan tred */
		pthread_cond_signal(&globalSignaler);
	}
	
	/* cekamo da se svi tredovi zavrse */
	for (int i = 0; i < numT; i++) {
		
		check_errorThread(pthread_join(tids[i], NULL), "...");
	}
	
	/* oslobadjamo resurse */
	free(tids);
	free(line);
	
	exit(EXIT_SUCCESS);
}