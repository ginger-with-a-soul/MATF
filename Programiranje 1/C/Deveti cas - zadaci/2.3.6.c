#include <stdio.h>

float stepen(float, int);

float stepen(float x, int n){
  int i = 0;
  float s = 1;
  if(n==0){
    s = 0;
  }
  while(i<n){
    s = x*s;
    i++;
  }  
return s;
}

int main(){
  float x;
  int n;
  scanf("%f %i", &x, &n);
  printf("%.4f\n", stepen(x, n));
return 0;
}