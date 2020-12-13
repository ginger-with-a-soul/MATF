#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
double x, y, min, max, f;
printf("Unesite dva realna broja ciju vrednost po datoj formuli zelite da izracunate: ");
scanf("%lf %lf", &x, &y);
min = x>=y? y : x;
max = x>=y? x : y;
f = (min+0.5)/(pow(max,2)+1);
printf("Rezultat je: %.2lf\n", f);
return 0;
}
