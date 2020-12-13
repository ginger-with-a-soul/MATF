#include <stdio.h>

#define MAX_POENA 100
#define MIN_POENA 0
#define MAX_UNOSA 300

typedef struct student{
  char indeks[9];
  int poeni;
}student;

int main(){
  
  student niz[MAX_UNOSA];
  
  int n, i = 0, br = 0, izlaz[MAX_UNOSA];
  double suma = 0, prolaz;
  
  scanf("%i", &n);
  
  if(n<0 || n>MAX_UNOSA){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    scanf("%s %i", niz[i].indeks, &niz[i].poeni);
    if(niz[i].poeni<MIN_POENA || niz[i].poeni>MAX_POENA){
      printf("-1\n");
      return -1;
    }
    suma += niz[i].poeni;
  }
  
  prolaz = (double)suma/n - 10;
  
  for(i = 0;i<n;i++){
    if(niz[i].poeni>=prolaz){
      izlaz[br++] = i;
    }
  }
  
  for(i = 0;i<br;i++){
    printf("%s\n", niz[izlaz[i]].indeks);
  }
  
  
  
  
  
  return 0;
}