#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#define check_error(expr, userMsg) \
	do {\
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE);\
		}\
	} while (0)

#define check_errorP(expr, userMsg) \
	do {\
		int _err = expr; \
		if (_err > 0) {\
			errno = _err; \
			check_error(0, userMsg);\
		}\
	} while (0)

/* globalne promenljive */
int maxC;			/* karakter koji se javlja najvise puta */
int numC;			/* broj pojavljivanja karaktera */
int initialized;	/* flag koji govori da li su brojaci inicijalizovani */
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER; /* staticka inicijalizacija muteksa */

/* ulazni podaci za nit */
typedef struct {
	
	char* path;	/* putanja do fajla */
	char c;		/* karakter koji nit treba da broji */
} threadArg_t;

/* izlazni argumenti niti */
typedef struct {
	
	char c;		/* karakter koji je nit brojala */
	int num;	/* broj pojavljivanja karaktera */
} threadOutArg_t;

/* funkcija koja implementira nit */
void* threadFunc(void* arg) {
	
	/* citamo ulazne argumente */
	threadArg_t* a = (threadArg_t*)arg;
	char c;
	/* otvaramo fajl u niti 
	 * BITNO:
	 * otvaranje fajla u niti dozvoljava da veci broj niti
	 * konkurentno cita isti fajl bez da imaju medjusobni uticaj na fajl ofset. Klucna rec je cita. 
	 * Kada se pisanje ukljuci u pricu, sinhronizacija nije bas naivna. 
	 *
	 * U slucaju kada fajl otvori jedna nit i prosledi pokazivac na fajl strim ostalim nitima
	 * (npr. otvorimo fajl u main-u i zapakujemo FILE* u argument niti) desice se katastrofa. Jedna nit
	 * pomera ofset za onoliko karaktera koliko je procitala, ali druga nit kada dobije kontrolu nad procesorom
	 * pomera taj isti fajl ofset bez znanja prve itd. Na taj nacin dobijate nekontrolisano pomeranje ofseta
	 * i situaciju koju je nemoguce zidebagovati ako ne znate unapred da bas tu mozete da pogresite i kako se
	 * ta greska manifestuje. 
	 */
	FILE* f = fopen(a->path, "r");
	
	/* alociramo prostor na hipu za povratnu vrednost iz niti.
	 * BITNO:
	 * povratna vrednost mora da se alocira na hipu. Vracanje lokalne promenljive iz niti je momentalni seg fault.
	 * Nit je samo stek okvir i kada se zavrsi, taj stek okvir se brise. U slucaju da vratite lokalnu promenljivu, 
	 * vratili ste adresu koja ne postoji, tj. deo je vec obrisanog stek okvira. Zato uvek alocirajte na hipu.
	 *
	 * BITNO 2:
	 * trik sa povratnom vrednosti iz niti je ovde jednostavno zaobilazenje uslova iz zadatka. U zadatku stoji recenica
	 * da ne treba da pamtite pojavljivanja slova u globalnom nizu, ali da ipak treba da ih odstampate redom, a, b, c, d itd. 
	 * Niti se izvrsavaju nedefinisanim redosledom, pa je printf u niti ocajno resenje, jer ne znate kada ce se koja nit zavrsiti. 
	 * Resenje je da se setite kako ustvari upravljate nitima. Prvo pokrecete niti redom, tj. prvo nit koja broji pojavljivanja slova a,
	 * pa slova b, pa slova c, itd. 
	 * Kada ih spajate nazad, join pozivate istim onim redom kojim ste ih pokretali. Dakle, prvo cekate da se zavrsi nit koja broji a, 
	 * nit koja broji b itd. Iako svaka ta nit moze da se izvrsi u proizvoljnom trenutku, obrada kraja je uvek deterministicka i ide onim
	 * redom kojim ste ih pokretali. To odmah treba da vas asocira na povratne vrednosti niti i da tako treba da uradite zadatak.
	 */
	threadOutArg_t* localCnt = malloc(sizeof(threadOutArg_t));
	check_error(localCnt != NULL, "...");
	
	/* inicijalizujemo povratnu vrednost niti */
	localCnt->c = a->c;
	localCnt->num = 0;
	
	/* brojimo slova sve do kraja fajla */
	while ((c=fgetc(f)) != EOF) {
		
		/* tolower, jer je u uslovu zadatka navedeno da se ne razlikuju mala i velika slova */
		if (tolower(c) == a->c)
			localCnt->num++;
	}
	
	fclose(f);
	
	/* zakljucavamo kriticnu sekciju */
	check_errorP(pthread_mutex_lock(&globalLock), "...");
	/* ako je promenljiva inicijalizovana */
	if (initialized) {
		/* po potrebi modifikujemo */
		if (localCnt->num > numC) {
			
			maxC = localCnt->c;
			numC = localCnt->num;
		}
	}
	/* ako nije */
	else {
		/* inicijalizujemo */
		maxC = localCnt->c;
		numC = localCnt->num;
		
		/* i dizemo flag */
		initialized = 1;
	}
	check_errorP(pthread_mutex_unlock(&globalLock), "...");
	
	/* vracamo rezultat izvrsavanja */
	return localCnt;
}

int main(int argc, char** argv) {
	
	check_error(argc == 2, "...");
	
	/* alociramo potrebne resurse */
	pthread_t* tids = malloc(sizeof(pthread_t)*26);
	check_error(tids != NULL, "...");
	threadArg_t* args = malloc(sizeof(threadArg_t)*26);
	check_error(args != NULL, "...");
	
	/* startujemo niti */
	for (int i = 0; i < 26; i++) {
		
		args[i].c = 'a' + i;
		args[i].path = argv[1];
		check_errorP(pthread_create(&tids[i], NULL, threadFunc, &args[i]), "...");
	}
	
	/* cekamo da se niti zavrse */
	for (int i = 0; i < 26; i++) {
		
		/* hvatamo povratnu vrednost niti */
		threadOutArg_t* a = NULL;
		check_errorP(pthread_join(tids[i], (void**)&a), "...");
		/* stampamo broj pojavljivanja slova */
		printf("%c:%d\n", a->c, a->num);
		/* oslobadjamo alociranu povratnu vrednost
		 *
		 * BITNO:
		 * svaka nit alocira prostor za povratnu vrednost. 
		 * Kada iskoristimo povratnu vrednost i kada nam ta informacija vise ne treba, 
		 * moramo da je oslobodimo u suprotnom imacemo ozbiljno curenje memorije
		 */
		free(a);
	}
	
	/* stampamo karakter koji se najvise puta javio u fajlu */
	printf("%c:%d\n", maxC, numC);
	
	/* oslobadjamo resurse */
	free(tids);
	free(args);
	
	exit(EXIT_SUCCESS);
}
