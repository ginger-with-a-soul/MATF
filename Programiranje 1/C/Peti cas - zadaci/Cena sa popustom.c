#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
unsigned a, b, c;
printf("Unesite cene Vasa 3 artikla: ");
scanf("%u %u %u", &a, &b, &c);
if(a<=0 || b<=0 || c<=0)
	printf("Nepravilan unos!\n");
else if(a<=b && a<=c)
	printf("Cena sa popustom je: %u\nUsteda: %u\n", 1+b+c, a-1);
else if(b<=a && b<=c)
	printf("Cena sa popustom je: %u\nUsteda: %u\n", 1+a+c, b-1);
else
	printf("Cena sa popustom je: %u\nUsteda: %u\n", 1+a+b, c-1);
return 0;
}
