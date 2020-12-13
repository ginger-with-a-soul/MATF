#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
int x, y, z;
printf("Unesite neka 3 cela broja: ");
scanf("%d %d %d", &x, &y, &z);
printf("Aritmeticka sredina Vasih brojeva je: %.2f\n", (x+y+z)/3.0);
return 0;
}
