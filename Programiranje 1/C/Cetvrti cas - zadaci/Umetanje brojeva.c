#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
unsigned x, y, levo, desno;
printf("Unesite neki prirodan broj: ");
scanf("%u", &x);
printf("Unesite neki dvocifren prirodan broj: ");
scanf("%u", &y);
levo = x/1000*100000;
desno = x%1000;
x = levo+y*1000+desno;
printf("Vas novi broj je: %u", x);
return 0;
}
