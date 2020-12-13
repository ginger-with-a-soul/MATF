#include <stdio.h>

#define MAX 52

typedef struct Pecivo{
  char ime[MAX];
  double cena;
}Pecivo;

int main(){
  
  int n, i = 0;
  double suma = 0, max = 0;
  
  scanf("%i", &n);
  
  if(n<1){
    printf("-1\n");
    return -1;
  }
  
  Pecivo niz[n];
  
  for(i = 0;i<n;i++){
    getchar();
    fgets(niz[i].ime, MAX, stdin);
    scanf("%lf", &niz[i].cena);
    if(niz[i].cena < 1){
      printf("-1\n");
      return -1;
    }
    if(niz[i].cena >= max){
      max = niz[i].cena;
      suma += max;
    }
  }
  
  printf("\n%.2lf\n", suma);
  
  return 0;
}