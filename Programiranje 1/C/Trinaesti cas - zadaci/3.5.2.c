#include <stdio.h>

typedef struct Razlomak{
  int imenilac[50];
  int brojilac[50];
}razlomak;

int suma_razlomaka(razlomak niz, int n);

razlomak proizvod_razlomak(razlomak niz, int n);

int suma_razlomaka(razlomak niz, int n){
 
}

razlomak proizvod_razlomak(razlomak niz, int n){
  razlomak int proizvod[100];
  proizvod.imenilac[0] = 1;
  proizvod.brojilac[0] = 1;
  int i = 0;
  for(i = 0;i<n;i++){
    proizvod.imenilac[0] *= niz.imenilac[i];
    proizvod.brojilac[0] *= niz.brojilac[i];
  }
  return proizvod;
  
}

int main(){
  int n, i = 0;
  razlomak int niz, proizvod;
  scanf("%i", &n);
  if(n<1){
    printf("-1\n");
    return -1;
  }
  for(i = 0;i<n;i++){
    scanf("%i %i", &niz.imenilac[i], &niz.brojilac[i]);
  }
  suma_razlomaka(niz, n);
  
  proizvod_razlomak(niz, n);
  
  printf("%i/%i\n%i\n", proizvod.brojilac[0], proizvod.imenilac[0]);
  
  return 0;
}