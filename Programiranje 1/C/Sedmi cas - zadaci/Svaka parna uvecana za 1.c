#include <stdio.h>

int main(){

	unsigned n;

	scanf("%u", &n);
	if(n<1){
		printf("-1\n");
		return -1;
	}

	if(n/10==0){
		if(n%2==0){
			n += 1;
		}

		printf("%u", n);
		return 0;
	}

	while(n/10!=0){
		if(n%2==0){
			n = n%1;
		}
		nn = n;
		n /= 10;



	}










return 0;
}
