#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#include <pthread.h>
#include <ctype.h>

#define osErrorFatal(userMsg) osErrorFatalImpl((userMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, userMsg) \
    do { \
        if (!(expr)) \
            osErrorFatal(userMsg); \
    } while(0)

#define osCheckPthread(pthreadErr, userMsg) \
    do { \
      int __pthreadErr = (pthreadErr); \
      if (__pthreadErr > 0) { \
        errno = __pthreadErr; \
        osAssert(false, userMsg); \
      } \
    } while (0)    


#define MAX_SIZE (128)

/* globalne promenljive koje se dele izmedju niti */
int globalSync = 0;
char buffer[MAX_SIZE];

/* mutex kojim sinhronizujemo pristup deljenim promenljivima */
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;
/* uslovna promenljiva kojom budimo tredove */
pthread_cond_t globalSignaler = PTHREAD_COND_INITIALIZER; 

void *osThreadFunction(void* arg) {
	
	/* kastujemo ulazni argument u odgovarajuci tip i 
	 * pamtimo lokalni index niti
	 */  
	int index = (int)(intptr_t) arg;
	
	/* BITNO:
	 * nit treba da se vrti sve dok se ne ispuni neki uslov,
	 * dakle mora da bude implementirana kao while(1) petlja
	 */
	while (1) {
		
		/* pokusavamo da uhvatimo mutex */
		osCheckPthread(pthread_mutex_lock(&globalLock), "locking failed");
		/* ako nije bilo ulanih operacija */
		while (globalSync == 0) {
			/* uspavljujemo nit */
			osCheckPthread(pthread_cond_wait(&globalSignaler, &globalLock), "cond wait failed");
		}
		
		/* ako je unesena -1 kao signal za kraj */
		if (globalSync == -1) {
			/* otkljucavamo mutex */
			osCheckPthread(pthread_mutex_unlock(&globalLock), "unlocking failed");
			/* iskacemo iz petlje */
			break;
		}

		/* ako nije red na ovu nit da se izvrsava */
		if (index != globalSync) {
			/* oktljucavamo mutex i prepustamo kontrolu nekoj drugoj niti */
			osCheckPthread(pthread_mutex_unlock(&globalLock), "unlocking failed");
			/* prelazimo na narednu iteraciju */
			continue;
		}
		
		/* inicijalizujemo brojac maih slova */
		int count = 0;
		int i = 0;
		/* brojima mala slova u ucitanoj reci */
		for (i = 0; buffer[i] != 0; i++)
			if (islower(buffer[i]))
					count++;
		
		/* stampamo broj malih slova */
		printf("(%d,%d)\n", index, count);
		
		/* resetujemo signal na nulu da bismo omogucili novi unos */
		globalSync = 0;
		
		/* otkljucavamo mutex */
		osCheckPthread(pthread_mutex_unlock(&globalLock), "locking failed");
	}
	
	/* vracamo NULL kao povratnu vrednost */
	return NULL;
}

int main(int argc, char** argv) {

	osAssert(argc == 2, os_Usage);
	
	/* alociramo prosto za niti */
	int numOfThreads = atoi(argv[1]);
	
	pthread_t* tids = malloc(numOfThreads*sizeof(pthread_t));
	osAssert(tids != NULL, "allocation failed");
	
	/* u petlji startujemo niti */
	int i = 0;
	for (i = 0; i < numOfThreads; i++) {
		
		int index = i + 1;
		osCheckPthread(pthread_create(&tids[i], NULL, osThreadFunction, (void*)(intptr_t)index), "thread creation failed");
	}
	
	/* u beskonacnoj petlji */
	while (1) {
		
		/* pokusavamo da zakljucamo mutex */
		osCheckPthread(pthread_mutex_lock(&globalLock), "mutex lock failed");
		
		/* ako ulaz nije obradjen */
		if (globalSync != 0) {
			
			/* otkljucavamo mutex */
			osCheckPthread(pthread_mutex_unlock(&globalLock), "Unlock failed");
			/* prelazimo na novu iteraciju */
			continue;
		}
		
		/* ucitavamo broj */
		scanf("%d", &globalSync);
		
		/* ako je ucitani broj -1 */
		if (globalSync == -1) {
			
			/* otkljucavamo mutex */
			osCheckPthread(pthread_mutex_unlock(&globalLock), "Unlock failed");
			/* obavestavamo sve blokirane niti */
			osCheckPthread(pthread_cond_broadcast(&globalSignaler),"broadcasting failed");
			/* iskacemo iz petlje */
			break;
		}
		
		/* ucitavamo rec */
		scanf("%s", buffer);
		
		/* otkljucavamo mutex */
		osCheckPthread(pthread_mutex_unlock(&globalLock), "Unlock failed");
		/* obavestavamo sve blokirane niti */
		osCheckPthread(pthread_cond_broadcast(&globalSignaler),"broadcasting failed");
	}
	
	/* u petlji */
	for (i = 0; i < numOfThreads; i++) {
		
		/* join-ujemo niti ignorisuci eventualnu povratnu vrednost*/
		osCheckPthread(pthread_join(tids[i], NULL), "thread creation failed");
	}
	
	/* oslobadjamo memoriju */
	free(tids);
	
	exit(EXIT_SUCCESS);
}
