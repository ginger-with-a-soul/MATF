#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
unsigned a, s, d, j;
printf("Unesite neki ceo trocifren broj: ");
scanf("%u", &a);
s = a/100;
d = a/10%10;
j = a%10;
if(a<100 || a>999){
	printf("Neispravan unos!\n");
	return -1;
	}
if(a==pow(s,3)+pow(d,3)+pow(j,3))
	printf("Broj je Armstrongov!\n");
else
	printf("Broj nije Armstrongov!\n");
return 0;
}
