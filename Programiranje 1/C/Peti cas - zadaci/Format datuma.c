#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(){
unsigned dan, mesec;
int godina;
char t;
printf("Unesite datum u formatu dan.mesec.godina: ");
scanf("%u%c%u%c%i%c", &dan, &t, &mesec, &t, &godina, &t);
if(dan>31 || dan<=0 || mesec>12 || mesec<=0 || t!='.' || godina==0 || (mesec==4 && dan>=31) || (mesec==6 && dan>=31) || (mesec==9 && dan>=31) || (mesec==11 && dan>=31)){
	printf("Datum nije korektan!\n");
	return -1;
}
if(mesec==2 && godina%4!=0 && dan>=29){
	printf("Datum nije korektan!\n");
	return -1;
}
else
	printf("Datum je korektan!\n");
return 0;
}
