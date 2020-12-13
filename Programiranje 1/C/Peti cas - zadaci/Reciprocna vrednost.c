#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int a;
printf("Unesite neki ceo broj: ");
scanf("%i", &a);
if(a!=0)
	printf("Reciprocna vrednost unetog broja je: %.4f\n", 1.0/a);
else
	printf("Nula nije validan unos!\n");
return 0;
}
