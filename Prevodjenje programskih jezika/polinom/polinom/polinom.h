#ifndef _POLINOM_H_
#define _POLINOM_H_

#include <stdio.h>
#include <stdlib.h>

#define MAXSTEPEN 20

typedef struct {
  int stepen ;
  float koeficijenti[MAXSTEPEN+1];
}Polinom;

/* Funkcija koja dodaje koeficijent u vec postojeci polinom */
void dodaj_koeficijent(Polinom* p, float x);

/* Funkcija koja ispisuje polinom na stdout u citljivom obliku
   Polinom prenosimo po adresi, da bi ustedeli kopiranje cele strukture,
   vec samo prenosimo adresu na kojoj se nalazi polinom kog ispisujemo */
void ispisi(const Polinom* p);

Polinom saberi(const Polinom* p, const Polinom *q);
Polinom oduzmi(const Polinom* p, const Polinom *q);
Polinom pomnozi(const Polinom* p, const Polinom *q);

/* Unarni minus */
Polinom uminus(const Polinom* p);

/* Poredjenje polinoma */
int jednaki(const Polinom *p, const Polinom * q);

/* Funkcija racuna izvod polinoma p  */
Polinom izvod(const Polinom * p);

/* Funkcija racuna integral polinoma p sa slobodnim clanom x */
Polinom integral(const Polinom * p, float x);

/* Funkcija racuna vrednost polinoma p u tacki x Hornerovim algoritmom */
float vrednost(const Polinom *p, float x);
#endif
