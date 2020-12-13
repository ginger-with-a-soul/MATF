#include <stdio.h>

int kvadrat(int);

int kvadrat(int a){
  return a*a;
}


int main(){
  
  int n, i = 1, j = 1;  
  scanf("%i", &n);
  
  if(n<1){
    printf("-1\n");
    return -1;
  }
  
  while(i<=kvadrat(n)){
    while(j<=n){
      printf("%3i", i);
      j++;
      i++;
    }
    j = 1;
    printf("\n");
  }
  
return 0;
}