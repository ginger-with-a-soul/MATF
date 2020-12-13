#include <stdio.h>
#include <float.h>

int main(){

	int n, i = 0;
	double m, min = DBL_MAX;

	scanf("%i", &n);

	if(n<0){
		printf("-1\n");
		return -1;
	}
	else if(n==0){
		printf("Niste uneli odgovarajuc broj artikala!\n");
		return 0;
	}

	while(i<n){
		scanf("%lf", &m);
		if(m<0){
			printf("Cena artikla ne moze biti negativna!\n");
			return -1;
		}
		if(m<min){
			min = m;
		}
		i++;
		

	}

	printf("%lf\n", min);





return 0;
}
