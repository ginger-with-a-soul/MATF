#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	int a, b;

	a = rand();
	b = rand();

	srand(time(NULL)); /*funkcija srand generise seed za
						rand.
						Funkcija time meri vreme u sekundama od
						1.1.1970(epohe), povratna vrednost je time_t(2^32) i moze da se konvertuje
						u min, sat...
						time(NULL) meri vreme od EPOHE do trenutka poziva istog
						rand funcija kao povratnu vrednost daje pseudo-nasumican broj
						od 0 do 2^(15-1). Ako ne pozovemo srand pre rand onda rand ima default
						vrednost 1 -> rand()==rand(1) a inace se kao argument stavlja seed
						rand(1) uvek daje isti rezultat koji zavisi od trenutnog stanja
						u racunaru
						RAND_MAX je makro koji menja 2^(15-1)*/
	fprintf(stdout, "%i godina\nrandom R broj izmedju 0 i 1 %.2lf\nrandom broj bez seeda %i\nrandom broj bez seeda provera %i\n", (int)time(NULL)/31536000, (double)rand()/RAND_MAX, a, b);

	return 0;
}