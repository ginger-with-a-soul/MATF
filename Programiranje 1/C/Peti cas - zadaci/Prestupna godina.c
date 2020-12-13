#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int godina;
printf("Unesite godinu: ");
scanf("%i", &godina);
if(godina>0 && ((godina%4==0 && godina%100!=0) || godina%400==0))
	printf("Godina je prestupna!\n");
else
	printf("Godina nije prestupna!\n");
return 0;
}
