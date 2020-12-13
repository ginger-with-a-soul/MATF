#include <stdio.h>

int main(){

	int n, bp = 0, i = 0, m1 = 0;
	double m;
	
	scanf("%i", &n);

	if(n<0){
		printf("-1\n");
		return -1;
	}
	else if(n==0){
		printf("Broj promena je 0.\n");
		return 0;
	}


	while(i<n){
		scanf("%lf", &m);
		if((m<0 && m1>0) || (m>0 && m1<0) || (m==0 && m1<0)){
			bp++;
		}

		m1 = m;
		i++;
	}

	printf("%i\n", bp);



return 0;
}
