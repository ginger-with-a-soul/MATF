#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
unsigned x, levo, desno;
printf("Unesite prirodan broj: ");
scanf("%u", &x);
levo = x/100*10;
desno = x%100%10;
printf("Vas novi broj je: %u\n", levo+desno);
return 0;
}
