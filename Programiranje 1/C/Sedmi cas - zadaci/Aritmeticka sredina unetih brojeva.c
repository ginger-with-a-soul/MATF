#include <stdio.h>

int main(){
	
	int n, i = 0, z = 0;
	double as = 0;
	scanf("%i", &n);
	z += n;
	i++;
	
	if(n==0){
		printf("-1\n");
		return -1;
	}

	while(n!=0){
		scanf("%i", &n);
		z += n;
		as = (double)z/(double)i;
		i++;
	}

	printf("%.4lf\n", as);

return 0;
}
