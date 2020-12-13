/* program ilustruje upotrebu detached tredova i prekidanje
 * celog programa onog momenta kada se pozove exit() u bilo kom tredu
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
#include <math.h>

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

/* implementacija niti */
void* threadFunc(void* arg) {
	
	/* uspavljujemo tred na 2 sekunde */
	sleep(2);
	/* stampamo neku poruku */
	printf("Hello from detached thread\n");
	
	/* prekidamo poruku */
	return NULL;
}

int main(int argc, char** argv) {
	
	/* kreiramo tred */
	pthread_t tid;
	pthread_create(&tid, NULL, threadFunc, NULL);
	/* otkacinjemo ga od trenutnog procesa -> nesto slicno daemon procesima
	 * koje nismo pominjali. Pogledati u TLPI ako vas zanima
	 * 
	 * Detach procese ne morate da hvatate sa join. ali morate da bude obazrivi
	 * da im ostavite dovoljno vremena da se zavrse, jer ako pozovete exit iz nekog
	 * drugog treda pre nego sto se detached zavrsi, prekinucete ga nasilno. 
	 */ 
	pthread_detach(tid);
	
	/* stampamo poruku */
	printf("Detached thread created\n");
	/* cekamo da se zavrsi detachovani tred.
	 * iskomentarisite ovu liniju i videcete da ce exit u "glavnom" tredu
	 * da prekine i detachovani tred 
	 */ 
	sleep(3);	
	
	
	exit(EXIT_SUCCESS);
}
