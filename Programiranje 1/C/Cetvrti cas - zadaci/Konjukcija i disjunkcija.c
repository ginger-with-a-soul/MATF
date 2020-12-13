#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
int x, y, rb, pb, pbmij100;
printf("Unesite dva cela broja: ");
scanf("%d %d", &x, &y);
rb = x!=y;
pb = (x%2==0 && y%2==0);
pbmij100 = (x>=0 && x<=100 && y>=0 && y<=100);
printf("Razliciti su: %d\nI x i y su parni: %d\nI x i y su i pozitivni i ne veci od 100: %d\n", rb, pb, pbmij100);
return 0;
}
