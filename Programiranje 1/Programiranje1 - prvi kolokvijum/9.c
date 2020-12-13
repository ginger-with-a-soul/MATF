#include <stdio.h>


int main(){

	int a;
	
	scanf("%i", &a);

	if(a<1){
		printf("-1\n");
		return -1;
	}

	while(a%10==0){
		a /= 10;
	}

	printf("%i\n", a);


return 0;
}
