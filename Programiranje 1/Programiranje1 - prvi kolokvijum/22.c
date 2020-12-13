#include <stdio.h>
#include <stdlib.h>


int main(){

	int n, m, i = 0, max = 0, nd, abs_m;
	scanf("%i", &n);
	if(n<0){
		printf("-1\n");
		return -1;
	}
	else if(n==0){
		printf("0\n");
		return 0;
	}


	while(i<n){
		scanf("%i", &m);
		abs_m = m;
		if(m<0){
			abs_m = abs(m);
		}
		if(abs_m%100>max){
			max = abs_m%100;
			nd = m;
		}
		i++;
	}

	printf("%i\n", nd);

return 0;
}
