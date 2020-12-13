#include <stdio.h>

float aritmeticka_sredina(int);

float aritmeticka_sredina(int a){
  a = a<0? -a : a;
  int i = 1;
  float as = 0, z;
  while(a!=0){
    as = as + a%10;
    z = as/i;
    a /= 10;
    i++;
  }
return z;
}

int main(){
  int a;
  scanf("%i", &a);
  printf("%.3f\n", aritmeticka_sredina(a));
return 0;
}