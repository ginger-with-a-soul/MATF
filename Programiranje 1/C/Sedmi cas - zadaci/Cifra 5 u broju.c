#include <stdio.h>

int main(){

	int n;
	scanf("%i", &n);

	if(n<0){
		printf("-1\n");
		return -1;
	}

	while(n/10!=0){
		if(n%10==5){
			printf("Cifra 5 se nalazi u broju!\n");
			return 0;
		}
		n /= 10;

	}

	if(n%10==5)
			printf("Cifra 5 se nalazi u broju!\n");
	else
		printf("Cifra 5 se ne nalazi u broju!\n");

return 0;
}
