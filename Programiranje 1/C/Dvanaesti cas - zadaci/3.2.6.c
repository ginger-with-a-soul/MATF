#include <stdio.h>

void trajanje_filma(int *sek, int *min, int *sat);

void trajanje_filma(int *sek, int *min, int *sat){
  *sat = *sek/3600;
  *min = *sek/60 - *sat*60;
  *sek = *sek - *min*60 - *sat*3600;
}

int main(){
  int sek, min, sat;
  scanf("%i", &sek);
  
  trajanje_filma(&sek, &min, &sat);
  
  printf("%i %i %i\n", sat, min, sek);
  
  return 0;
}