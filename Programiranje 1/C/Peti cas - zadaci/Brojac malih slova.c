#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
char a, b, c, d, e;
int b_m = 0;
printf("Unesite 5 karaktera odvojenih razmakom: ");
scanf("%c %c %c %c %c", &a, &b, &c, &d, &e);
if(a>='a' && a<='z')
	++b_m;
if(b>='a' && b<='z')
	++b_m;
if(c>='a' && c<='z')
	++b_m;
if(d>='a' && d<='z')
	++b_m;
if(e>='a' && e<='z')
	++b_m;
printf("Broj malih slova je: %i\n", b_m);
return 0;
}
