#include <stdio.h>

int main(){
  int n, i = 0, nn;
  
  scanf("%i", &n);
  nn = n;
  while(n){
    for(;n;){
      i++;
      n /= 10;
    }
    if(i%2){
      printf("%i ", nn);
    }
    i = 0;
    scanf("%i", &n);
    nn = n;
  }
  
  return 0;
}