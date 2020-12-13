#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
double x;
printf ("Unesite realan broj ciji kvadrat i kub zelite: ");
scanf ("%lf", &x); /*daje korisniku da sam unese zeljeni broj i taj unos dodeljuje promenljivoj x*/
printf("Kvadrat Vaseg broja je: %.2lf\n", pow(x, 2));/*ispisuje long float odnosno double vrednost koju izracunava kao kvadrat x-a i ispisuje to na 2 decimale. Da smo zeleli duzinu broja da bude npr. 6 i da ima 2 decimale onda bismo stavili %6.2lf*/
printf("Kub Vaseg broja je: %.2lf\n", pow(x, 3));
}
