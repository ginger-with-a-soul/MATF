#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(){
int a, b;
char c;
printf("Unesite dva cela broja i neki od operatora (*, /, %, +, -): ");
scanf("%i %i %c", &a, &b, &c);
if(b==0 && c=='/'){
	printf("Ne umem da podelim sa nulom!\n");
	return -1;
}
switch(c){
	case '*':
		printf("Rezultat je: %i\n", a*b);
	break;
	case '/':
		printf("Rezultat je: %i\n", a/b);
	break;
	case '%':
		printf("Rezultat je: %i\n", a%b);
	break;
	case '+':
		printf("Rezultat je: %i\n", a+b);
	break;
	case '-':
		printf("Rezultat je: %i\n", a-b);
	break;
	default:
		printf("Nepodrzan operator!\n");
	break;
}
return 0;
}
