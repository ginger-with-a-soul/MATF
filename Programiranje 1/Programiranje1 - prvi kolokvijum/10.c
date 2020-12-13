#include <stdio.h>
#include <stdlib.h>


int main(){

	int a, c;

	scanf("%i", &a);

	a = a<0? abs(a) : a;

	while(a*10/10!=0){
		c = a%10;
		printf("%i \n", c);
		a /= 10;
	}


return 0;
}
