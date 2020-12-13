#include <stdio.h>

#define MAX 3

typedef struct ELEMENT{
  char ime[MAX];
  int metal;
  float gramaza;
}ELEMENT;

int main(){
  int n, i = 0, j = 0;
  float suma = 0, sumaM = 0, pMetala, pNm;
  scanf("%i", &n);
  
  ELEMENT elementi[n];
  
  for(i = 0;i<n;i++){
    scanf("%s %i %f", elementi[n].ime, &elementi[n].metal, &elementi[n].gramaza);
    if(elementi[n].metal != 1 && elementi[n].metal != 0){
      printf("-1\n");
      return -1;
    }
    if(elementi[n].metal){
      sumaM += elementi[n].gramaza;
    }
    suma += elementi[n].gramaza;
  }
  
  if(suma<99 || suma>101){
    printf("-1\n");
    return -1;
  }
  
  pMetala = (float)sumaM*100/suma;
  pNm = 100 - pMetala;
  
  printf("\n%.2f %.2f\n", pMetala, pNm);
  
  
  
  return 0;
}