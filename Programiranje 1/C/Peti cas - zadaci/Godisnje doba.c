#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(){
unsigned d, m;
printf("Unesite dan i mesec: ");
scanf("%u %u", &d, &m);
if((d>20 && m==3) || (d<22 && m==6) || m==4 || m==5)
	printf("Prolece\n");
else if((d>21 && m==6) || (d<23 && m==9) || m==7 || m==8)
	printf("Leto\n");
else if((d>22 && m==9) || (d<22 && m==12) || m==10 || m==11)
	printf("Jesen\n");
else
	printf("Zima\n");
return 0;
}
