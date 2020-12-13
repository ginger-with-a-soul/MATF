#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, m, i = 0, d1, d2 = 0, max;

	scanf("%i", &n);
	if(n<0){
		printf("-1\n");
		return -1;
	}
	else if(n==0){
		printf("Niste uneli ni jedan broj!\n");
		return 0;
	}
	
	while(i<n){
		scanf("%i", &m);
		d1 = abs(m/10%10);
		if(d1>d2){
			d2 = d1;
			max = m;
		}
		i++;
	
	}


	printf("%i\n", max);


return 0;
}
