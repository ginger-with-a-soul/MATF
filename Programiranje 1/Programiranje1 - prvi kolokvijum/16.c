#include <stdio.h>


int main(){

	int n, p = 1, bp = 0;
	
	scanf("%i", &n);
	if(n==0){
		printf("-1\n");
		return -1;
	}
	else if(n>0){
		p *= n;

	}

	while(n!=0){
		scanf("%i", &n);
		if(n>0){
			p *= n;
			bp++;
		}
	}

	if(bp==0){
		printf("0\n");
		return 0;
	}

	printf("%i\n", p);



return 0;
}
