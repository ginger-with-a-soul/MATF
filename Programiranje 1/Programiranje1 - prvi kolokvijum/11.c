#include <stdio.h>


int main(){

	int n, n_n, s = 0;

	scanf("%i", &n);

	if(n<1){
		printf("-1\n");
		return -1;
	}

	n_n = n;

	while(n*10/10!=0){
		s = s + (n%10);
		n /= 10;
	}

	if(n_n%s==0){
		printf("Deljiv je sa sumom svojih cifara\n");
	}
	else{
		printf("Nije deljiv sa sumom svojih cifara\n");
	}


return 0;
}
