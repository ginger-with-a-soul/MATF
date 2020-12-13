#include <stdio.h>
#include <stdlib.h>

int faktorijel(int);

int faktorijel(int a){
  if(a<0 || a>12){
    exit(EXIT_FAILURE);
  }
  int z = 1;
  while(a!=0){
    z = a*z;
    a--;
  }
return z;
}

int main(){
  int x, y;
  scanf("%i %i", &x, &y);
  printf("%i\n", faktorijel(x) + faktorijel(y));
return 0;
}