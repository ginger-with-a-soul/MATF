#include <stdio.h>
#include <float.h>

int main(){

	int n, i = 0;
	float m, min = DBL_MAX;

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
		scanf("%f", &m);
		if(m<=0){
			printf("-1\n");
			return -1;		
		}		
		else if(m<min){
			min = m;
		}	
		i++;
	}

	printf("%f\n", min);


return 0;
}
