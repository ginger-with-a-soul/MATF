#include <stdio.h>


int main(){

	int n, i = 0, m, max = 0, br = 0, br2 = 0, n_m;

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
		n_m = m;
		while(m/10!=0){
			br++;
			m /= 10;
		}
		if(br>br2){
			max = n_m;
			br2 = br;
		}
		br = 0;
		i++;
	}


	printf("%i\n", max);


return 0;
}
