#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
float a, b, c, x1, x2, x, d;
printf("Unesite koeficijente kvaratne jednacine (a, b, c): ");
scanf("%f %f %f", &a, &b, &c);
d = pow(b,2)-(4*a*c);
x = -b/(2*a);
x1 = (-b+sqrt(pow(b,2)-4*a*c))/(2*a);
x2 = (-b-sqrt(pow(b,2)-4*a*c))/(2*a);
if(a==b && b==c)
	printf("Jednacina nema resenja!\n");
else if(d==0)
	printf("Jednacina ima jedno resenje i ono je: %.2f\n", -b/(2*a));
else if(d<0)
	printf("Jednacina ima dva konjugovano kompleksna resenja\n");
else
 printf("Jednacina ima dva realna resenja: %.2f\n %.2f\n", x1, x2);
return 0;
}
