#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, i = 0, m, abs_m, max = 0, max_c, br;

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
		while(abs_m/10!=0){
			br++;
			abs_m /= 10;
		}
		if(abs_m>max){
			max = abs_m;
			max_c = m;
		}
		i++;
	}


printf("%i\n", max_c);

return 0;
}
