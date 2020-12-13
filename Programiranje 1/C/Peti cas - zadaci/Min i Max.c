#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (){
int a, b;
printf("Unesite dva cela broja: ");
scanf("%i %i", &a, &b);
if(a>b)
	printf("Maksimum je: %i\nMinimum je: %i\n", a, b);
else
	printf("Maksimum je: %i\nMinimum je: %i\n", b, a);
return 0;
}
