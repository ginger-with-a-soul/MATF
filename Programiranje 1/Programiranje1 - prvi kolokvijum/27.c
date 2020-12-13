#include <stdio.h>
#include <math.h>


int main(){

	int n, n_n, m, br = 0;
	
	scanf("%i", &n);

	if(n<1){
		printf("-1\n");
		return -1;
	}

	n_n = n;

	while(n*10/10!=0){
		m = n%10;
		br++;
		if(m%2==0){
			m++;
			n_n = n_n-pow(10, br-1)*(m-1) + pow(10, br-1)*m;
		}
	n /= 10;
	}

printf("%i\n", n_n);

return 0;
}
