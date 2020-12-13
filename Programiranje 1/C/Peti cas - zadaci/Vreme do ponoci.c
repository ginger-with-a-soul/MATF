#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
int s, m, sve_ukupno, do_ponoci, sati, minuta;
printf("Unesite vreme (sate u intervalu od [0, 24), minute u intervalu od [0, 60) ");
scanf("%i %i", &s, &m);
sve_ukupno = s*60+m;
do_ponoci = 24*60-sve_ukupno;
sati = do_ponoci/60;
minuta = do_ponoci-(sati*60);
if(s>=0 && s<24 && m>=0 && m<60)
	printf("Do ponoci je ostalo %i sati i %i minuta\n", sati, minuta);
else
	printf("Los unos!\n");
return 0;
}
