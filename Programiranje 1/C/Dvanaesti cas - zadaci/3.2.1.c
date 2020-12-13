#include <stdio.h>

void poredi(int *a, int *b);

void poredi(int *a, int *b){
  int c;
  if(*a > *b){
    c = *b;
    *b = *a;
    *a = c;
  }
}

int main(){
  int a, b;
  scanf("%i %i", &a, &b);
  
  poredi(&a, &b);
  
  printf("%i %i\n", a, b);
  
  return 0;
}