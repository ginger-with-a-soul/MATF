#include <stdio.h>

int main(){
  
  unsigned int n, i = 0, j = 1;
  scanf("%u", &n);
  
  for(i = 0;i<n;i++){
    for(j = 1;j+i<=n;j++){
      printf("*");
    }
    printf("\n");
  }
  
return 0;
}