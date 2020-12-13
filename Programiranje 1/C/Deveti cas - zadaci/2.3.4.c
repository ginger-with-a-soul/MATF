#include <stdio.h>

int minimum (int, int, int);

int minimum(int a, int b, int c){
  a = a>b? b : a;
  a = a>c? c : a;
return a;
}

int main(){
  int x, y, z;
  scanf("%i %i %i", &x, &y, &z);
  printf("%i\n", minimum(x, y, z));
return 0;
}