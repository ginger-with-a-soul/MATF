#include <stdio.h>

int main(){
  
  int n, i = 1, j = 1;
  scanf("%i", &n);
  
  if(n<1){
    printf("-1\n");
    return -1;
  }
  
  while(i<=n){
    if(i==1 || i==n){
      while(j<=n){
        printf("*");
        j++;
      }
      j = 1;
    }
    else{
      while(j<=n){
      if(j==1 || j==n){
        printf("*");
        j++;
      }
      else{
        printf(" ");
        j++;
      }
      }
      j = 1;
    }  
    printf("\n");
    i++;
  }
  
return 0;
}