#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int a, h, s, j, d, p_p_c;
printf("Unesite cetvorocifren ceo broj: ");
scanf("%i", &a);
p_p_c = 1;
h = a/1000;
s = a/100%10;
d = a/10%10;
j = a%10;
if(a<0)
	a = abs(a);
if(a<999 || a>9999){
	printf("Neispravan unos!\n");
	return -1;
	}
if(h%2==0)
	p_p_c *= h;
if(s%2==0)
	p_p_c *= s;
if(d%2==0)
	p_p_c *= d;
if(j%2==0)
	p_p_c *= j;
if(p_p_c==1){
	printf("Nema parnih cifara!\n");
	return -1;
	}
printf("Proizvod parnih cifara je: %i\n", p_p_c);
return 0;
}
