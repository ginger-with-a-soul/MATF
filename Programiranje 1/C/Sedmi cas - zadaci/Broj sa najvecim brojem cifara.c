#include <stdio.h>

int main(){

	int n, m, max1 = 0, max2 = 0, nb = 0, i = 0, nm;

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
		nm = m;
		if(m/10==0){
		max1++;
		}
		while(m/10!=0){
			max1++;
			m /= 10;
		}
	
	if(max1>max2){
		max2 = max1;
		nb = nm;
	}

	max1 = 0;
	i++;
	}


	printf("%i\n", nb);


return 0;
}
