#include <stdio.h>

void kolicnik_i_ostatak(int *a, int *b);

void kolicnik_i_ostatak(int *a, int *b){
  if(*b){
    *a = 1;
  }
  else{
    *a = 0;
  }
}
int main(){
  int a, b;
  scanf("%i %i", &a, &b);
  kolicnik_i_ostatak(&a, &b);
  
  printf("%i\n", a);
  
  return 0;
}