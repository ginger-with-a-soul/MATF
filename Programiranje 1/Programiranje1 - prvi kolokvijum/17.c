#include <stdio.h>


int main(){

	int n;
	
	scanf("%i", &n);
	if(n<0){
		printf("-1\n");
		return -1;
	}

	while(n*10/10!=0){
		if(n%10==5){
			printf("Da\n");
			return 0;
		}
		n /= 10;

	}

	printf("Ne\n");


return 0;
}
