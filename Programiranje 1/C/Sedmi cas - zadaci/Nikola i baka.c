#include <stdio.h>

int main(){

	double m, c;
	int n, i = 0, b = 0;
	
	scanf("%lf %i", &m, &n);
	
	if(m<=0 || n<=0){
		printf("-1\n");
		return -1;
	}

	while(i<n){
		scanf("%lf", &c);
		if(c<0){
			printf("Artikal ne moze imati negativnu cenu!\n");
			return -1;
		}
		else if(m>=c)
			b++;
	
		i++;
	}
	
	printf("%i\n", b);


return 0;
}
