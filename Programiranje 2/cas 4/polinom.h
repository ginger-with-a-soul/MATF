#ifndef _POLINOM_H_
#define _POLINOM_H_ 0

void greska();
int* unos(int* n);
void ispis_polinoma(int* a, int n);
int* suma_polinoma(int* a, int n, int* b, int m, int* k);
void mnoz_skalarom(int *a, int n, int s);
int vr_poly(int* a, int n, int x);
int* mul_poly(int *a, int n, int* b, int m, int* k);

#endif