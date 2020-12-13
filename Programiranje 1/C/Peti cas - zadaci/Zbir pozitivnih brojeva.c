#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int a, b, c, zbir = 0;
printf("Unesite 3 cela broja: ");
scanf("%i %i %i", &a, &b, &c);
if(a>0)
	zbir += a;
if(b>0)
	zbir += b;
if(c>0)
	zbir += c;
printf("Zbir je: %i\n", zbir);
return 0;
}
