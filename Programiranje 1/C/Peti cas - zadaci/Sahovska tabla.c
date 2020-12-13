#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(){
unsigned x1, y1, x2, y2;
printf("Unesite koordinate prvog polja: ");
scanf("%u %u", &x1, &y1);
printf("Unesite koordinate drugog polja: ");
scanf("%u %u", &x2, &y2);
if(x1>8 || x1<1 || x2>8 || x2<1 || y1>8 || y1<1 || y2>8 || y2<1){
	printf("Neispravan unos!");
	return -1;
}
if((x1+y1)%2==(x2+y2)%2)
	printf("Polja su iste boje!\n");
else
	printf("Polja nisu iste boje!\n");
if((abs(x1-x2)>=2 || abs(y1-y2)>=2) && (abs(x1-x2)>=1 || abs(y1-y2)>=1) && (x1+y1)%2!=(x2+y2)%2)
	printf("Kraljica sa prvog polja ne ugrozava figuru sa drugog polja!\n");
else
	printf("Kraljica sa prvog polja ugrozava figuru sa drugog polja!\n");
if((abs(x1-x2)<=2 || abs(y1-y2)<=2) && (abs(x1-x2)<=1 || abs(y1-y2)<=1) && abs((x1+y1)-(x2+y2))<=3)
	printf("Konj sa prvog polja ugrozava figuru sa drugog polja!\n");
else
	printf("Konj sa prvog polja ne ugrozava figuru sa drugog polja!\n");
return 0;
}
