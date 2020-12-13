#include <stdio.h> /*ukljucuje osnovne definisane funkcije koje cemo koristiti (biblioteka osnovnih funkcija). Skraceno od Standard Input Output.header */
#include <math.h> /*sadrzi neke matematicke funkcije. Ukoliko koristimo ovu biblioteku onda obavezno kod gcc prevodjenja iz .c u .out NA KRAJU svega stavimo -lm*/
#include <stdlib.h> //u ovoj biblioteci se nalazi abs funkcija

int main() { /*int se koristi zbog 'return 0' (0 je ceo broj). Main je ime bloka naredbi koji ce slediti. Zagrade () sluze za upisivanje odredjenih argumenata, { oznacava pocetak bloka naredbi koje se na kraju zatvaraju sa }. Return 0 proverava da li je blok naredbi pravilan i ukoliko jeste on to signalizira programu*/
printf ("Zdravo\n"); /*printf se koristi za ispisivanje rezultata. \n kaze da se taj rezultat ispise u novom redu*/
return 0;
}
