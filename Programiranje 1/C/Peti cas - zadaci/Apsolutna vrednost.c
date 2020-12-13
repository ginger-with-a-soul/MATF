#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
float a;
printf("Unesite neki realan broj: ");
scanf("%f", &a);
if(a<0)
	printf("Apsolutna vrednost unetog broja je: %.2f\n", fabs(a));
else
	printf("Apsolutna vrednost unetog broja je: %.2f\n", a);
return 0;
}
