#include <stdio.h>


int main(){

	float m, c;
	int n, i = 0, br = 0;

	scanf("%f %i", &m, &n);

	if(m<=0 || n<1){
		printf("-1\n");
		return -1;
	}

	while(i<n){
		scanf("%f", &c);
		if(c<1){
			printf("-1\n");
			return -1;
		}
	else if(c<=m){
		br++;
	}

		i++;
	}

	printf("%i\n", br);


return 0;
}
