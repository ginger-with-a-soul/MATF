#include <stdio.h>

int main(){
  
  int n, i = 1, j = 1;
  scanf("%i", &n);
  
  for(i = 1;i<=n;i++){
    for(j = 1;j<=n;j++){
      if(i==j || i+j==n+1){
        printf("*");
      }
      else{
        printf(" ");
      }
    
    }
    printf("\n");
    j = 1;
  }
  
return 0;
}