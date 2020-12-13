#include <stdio.h>
#include <math.h>


int main(){

	int a, i, levo, desno;
	
	scanf("%i %i", &a, &i);

	if(i<=1 || a<0){
		printf("-1\n");
		return -1;
	}

	levo = a/(int)pow(10, i);
	desno = a%(int)pow(10, i-1);


	a = levo*(int)pow(10,i-1)+desno*(int)pow(10, i-1);

	printf("%i\n", a);
	

return 0;
}
