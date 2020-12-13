#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(){
int mesec, godina;
printf("Unesite mesec: ");
scanf("%i", &mesec);
printf("Unesite godinu: ");
scanf("%i", &godina);
if(godina<0)
	godina = abs(godina);
if(mesec==1)
	printf("Januar; 31 dan\n");
else if(mesec==2 && ((godina%4==0 && godina%100!=0) || godina%400==0))
	printf("Februar; 29 dana\n");
else if(mesec==2 && ((godina%4!=0 || godina%400!=0)))
	printf("Februar; 28 dana\n");
else if(mesec==3)
	printf("Mart; 31 dan\n");
else if(mesec==4)
	printf("April; 30 dana\n");
else if(mesec==5)
	printf("Maj; 31 dan\n");
else if(mesec==6)
	printf("Jun; 30 dana\n");
else if(mesec==7)
	printf("Jul; 31 dan\n");
else if(mesec==8)
	printf("Avgust; 31 dan\n");
else if(mesec==9)
	printf("Septembar; 30 dana\n");
else if(mesec==10)
	printf("Oktobar; 31 dan\n");
else if(mesec==11)
	printf("Novembar; 30 dana\n");
else if(mesec==12)
	printf("Decembar; 31 dan\n");
else
	printf("Neispravan unos meseca!\n");
return 0;
}
