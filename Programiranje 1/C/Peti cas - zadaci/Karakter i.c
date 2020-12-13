#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(){
char i = getchar();
if(islower(i))
	printf("%c\n", toupper(i));
else if(isupper(i))
	printf("%c\n", tolower(i));
else if(isdigit(i))
	printf("Cifra\n");
else
	printf("*%c*\n", i);
return 0;
}
