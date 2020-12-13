#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
unsigned x, y, z, levo, desno;
printf("Unesite neki prirodan broj: ");
scanf("%u", &x);
printf("Poziciju na koju zelite da umetnete neku cifru: ");
scanf("%u", &y);
printf("Cifru koju zelite da umetnete: ");
scanf("%u",&z);
levo = x/(unsigned)pow(10, y);
desno = x%(unsigned)pow(10, y);
x = levo*(unsigned)pow(10,y+1)+z*(unsigned)pow(10,y)+desno;
printf("Vas novi broj je: %u\n", x);
return 0;
}
