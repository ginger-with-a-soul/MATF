#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int b_c = 0;
char a, b, c, d, e;
printf("Unesite 5 karaktera bez razmaka izmedju njih: ");
scanf("%c%c%c%c%c", &a, &b, &c, &d, &e);
if(a>='0' && a<='9')
	++b_c;
if(b>='0' && b<='9')
	++b_c;
if(c>='0' && c<='9')
	++b_c;
if(d>='0' && d<='9')
	++b_c;
if(e>='0' && e<='9')
	++b_c;
printf("Broj cifara je: %i\n", b_c);
return 0;
}	
