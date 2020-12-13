#include <stdio.h>
#include <stdlib.h>


int main(){

	int n, i = 1, bp = 0;
	float m, m1;
	
	scanf("%i", &n);
	if(n<0){
		printf("-1\n");
		return -1;
	}
	else if(n==0){
		printf("0\n");
		return 0;	
	}

	scanf("%f", &m1);

	while(i<n){
		scanf("%f", &m);
		if((m1>=0 && m<0) || (m1<0 && m>=0)){
			bp++;
		}
		m1 = m;
		i++;
	}

	printf("%i\n", bp);


return 0;
}
