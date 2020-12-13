#include <stdio.h>

int main(){
  
  unsigned int n, i = 1, j = 1;
  scanf("%u", &n);
  
  for(i = 1;i<=n;i++){
    for(j = 1;j<=n;j++){
      if((j%n==j && j==n/2.0+0.5) || (i%n==i && i==n/2.0+0.5)){
        printf("+");
      }
      else{
        printf(" ");
      }
    }
    j = 1;
    printf("\n");
  }
return 0;  
}