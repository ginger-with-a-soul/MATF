#include <stdio.h>

int main(){

	double v, max, min;

	scanf("%lf", &v);
	if(v==0){
		printf("Niste uneli brojeve!\n");
		return 0;
	}
	max = v;
	min =v;

	while(v!=0){
		scanf("%lf", &v);
		if(v>max && v!=0){
			max = v;
		}
		if(v<min && v!=0){
			min = v;
		}

	}

	printf("%lf\n", max-min);



return 0;
}
