#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int a;
printf("Unesite ceo broj proizvoljne duzine: ");
scanf("%i", &a);
if(a==0)
	printf("Broj je nula!\n");
else if(a>0)
	printf("Broj je veci od nule!\n");
else
	printf("Broj je manji od nule!\n");
return 0;
}
