#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
float cm, in;
printf("Unesite Vas broj inca: ");
scanf("%f", &cm);
in = 2.54;
printf("%.2f in = %.2f cm\n", cm, cm*in);
return 0;
}
