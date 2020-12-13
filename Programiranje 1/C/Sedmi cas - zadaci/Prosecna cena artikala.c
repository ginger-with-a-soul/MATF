#include <stdio.h>

int main(){

	double n, pc, u = 0;
	int i = 0;

	scanf("%lf", &n);
	u += n;

	if(n<0){
		printf("Cena ne moze biti negativna!\n");
		return -1;
	}
	else if(n==0){
		printf("Nisu unete cene!\n");
		return -1;
	}
	
	while(n>0){
		scanf("%lf", &n);
		if(n<0){
			printf("Cena ne moze biti negativna!\n");
			return -1;
		}
		u += n;
		i++;
		pc = u/i;

	}
	
	


	printf("%.4lf\n", pc);


return 0;
}
