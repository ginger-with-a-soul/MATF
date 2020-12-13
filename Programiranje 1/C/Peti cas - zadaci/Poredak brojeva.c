#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
signed a;
int h, s, d, j;
printf("Unesite oznacen cetvorocifren broj: ");
scanf("%i", &a);
if(a<0)
	a = abs(a);
if(a<999 || a>9999){
	printf("Uneti broj nije cetvorocifren!\n");
	return -1;
	}
h = a/1000;
s = a/100%10;
d = a/10%10;
j = a%10;
if(h>s && s>d && d>j)
	printf("Cifre su uredjene opadajuce!\n");
else if(h<s && s<d && d<j)
	printf("CIfre su uredjene rastuce!\n");
else if(h==s && s==d && d==j)
	printf("Sve cifre su jednake!\n");
else if(h>=s && s>=d && d>=j)
	printf("Cifre su uredjene nerastuce!\n");
else if(h<=s && s<=d && d<=j)
	printf("Cifre su uredjene neopadajuce!\n");
else
	printf("Cifre nisu uredjene!\n");
return 0;
}
