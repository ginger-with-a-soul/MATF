/* program ilustruje sinhronizaciju niti pomocu atomicnih promenljivih 
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
#include <math.h>

/* zaglavlje neophodno za upotrebu atomicnih promenljivih */
#include <stdatomic.h>

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

/* definisemo atomicnu promenljivu */
atomic_int GlobalSum;

/* implementacija niti */
void* threadFunc(void* arg) {
	
	/* inicijalizujemo pokazivac na putanju do fajla */
	char* filePath = (char*)arg;
	
	/* otvaramo fajl
	 * 
	 * BITNO:
	 * fajlovai se uvek otvaraju u tredu.
	 * Tredu se nikada ne prosledjuje vec otvoreni fajl stream, jer to pravi
	 * haos u programu. Tredovi ce jedan drugom gaziti fajl offset i dobicete
	 * katastrofu koju necete uspeti da izdebagujete.
	 */ 
	FILE* f = fopen(filePath,"r");
	check_error(f != NULL, "...");
	
	/* izracunavamo lokalnu sumu */
	int localSum = 0;
	int x;
	while (fscanf(f, "%d", &x) == 1) {
		localSum += x;
		/* izazov da napisete sledecu naredbu je veliki, ali je takva organizacija
		 * koda potpuno besmislena jer ponistava potrebu za tredovima. Pored besmisla,
		 * kaznjava vas sa najmanje 50% na zadatku.
		 * 
		 * Sa sledecom linijom biste dobili program koji je sporiji od klasicnog
		 * sekvencijalnog programa koji u petlji obradjuje fajl po fajl.
		 */ 
		//atomic_fetch_add(&GlobalSum, x);
	}
	
	/* proveravamo da li smo obradili ceo fajl i zatvaramo ga */
	check_error(feof(f),"...");	
	fclose(f);
	
	/* tek na kraju uvecavamo globalnu sumu
	 * 
	 * Na ovaj nacin dobijamo program koji nezavisno i "paralelno" obradjuje
	 * fajlove. Nakon obrade upisuje rezultat u globalnu sumu. 
	 * 
	 * Plasticno, ako imate 10 fajlova sa po 1 000 000 brojeva, nezavisno
	 * biste sabrali svih tih 10x po 1000000 brojeva i tek onda biste uvecali globalnu
	 * promenljivu 10 puta, sto je 10 sinhronih pristupa.
	 * 
	 * U suprotnom, pogresno resenje iz linije 73, bi znacilo da za svaki broj koji
	 * ucitate sinhrono pristupe deljenoj promenljivoj, sto se prevodi u 10 000 000
	 * sinhronih operacija, sto je ogromno usporenje programa i prakticno
	 * ga prevodi u klasicni sekvencijalni program samo mnogo puta sporiji. 
	 */ 
	atomic_fetch_add(&GlobalSum, localSum);
	
	return NULL;
}

int main(int argc, char** argv) {
	
	check_error(argc > 1, "....");
	
	/* alociramo prostor za ID-eve */
	int numThreads = argc-1;
	pthread_t* tids = malloc(numThreads*sizeof(pthread_t));
	check_error(tids != NULL, "...");
	
	/* inicijalizujemo globalnu atomicnu promenljivu 
	 * BITNO:
	 * sa atomicnim promenljivama nema klasicnih aritmetickih operacija i dodele 
	 * sve operacije sa atomicnim promenljivama se rade pomocu funkcija iz
	 * stdatomic.h
	 */
	atomic_init(&GlobalSum, 0); 
	
	/* startujemo tredove */
	for (int i = 0; i < numThreads; i++) {
		
		check_errorThread(pthread_create(&tids[i], NULL, threadFunc, argv[i+1]), "...");
	}
	
	/* cekamo da se zavrse */
	for(int i = 0; i < numThreads; i++) {
		
		check_errorThread(pthread_join(tids[i], NULL), "...");
	}
	
	/* stampamo rezultat izvrsavanja, tj. zbir svih brojeva u fajlovima */
	printf("Total sum: %d\n", atomic_load(&GlobalSum));
	
	/* oslobadjamo resurse */
	free(tids);
	
	exit(EXIT_SUCCESS);
}
