#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int b_a_A = 0;
char a, b, c, d, e;
printf("Unesite 5 karaktera bez razmaka izmedju njih: ");
scanf("%c%c%c%c%c", &a, &b, &c, &d, &e);
if(a=='a' || a=='A')
	++b_a_A;
if(b=='a' || b=='A')
	++b_a_A;
if(c=='a' || c=='A')
	++b_a_A;
if(d=='a' || d=='A')
	++b_a_A;
if(e=='a' || e=='A')
	++b_a_A;
printf("Broj malih i velikih slova 'a' je: %i\n", b_a_A);
return 0;
}
