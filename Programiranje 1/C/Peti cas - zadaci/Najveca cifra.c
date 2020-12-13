#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int a, h, s, d, j;
printf("Unesite neki cetvorocifren broj: ");
scanf("%i", &a);
if(a<0)
	a = abs(a);
h = a/1000;
s = a/100%10;
d = a/10%10;
j = a%10;
if(a/1000==0 || a/10000!=0)
	printf("Unos je neispravan!\n");
else if(h>=s && h>=d && h>=j)
	printf("Najveca cifra je: %i\n", h);
else if(s>=h && s>=d && s>=j)
	printf("Najveca cifra je: %i\n", s);
else if(d>=h && d>=s && d>=j)
	printf("Najveca cifra je: %i\n", d);
else
	printf("Najveca cifra je: %i\n", j);
return 0;
}
