#include <stdio.h>

#define max 10

int main(){
  int a[max], i = 0, x, bp = 0;
  while(i<max){
    scanf("%i", &a[i]);
    i++;
  }
  i = 0;
  
  while(i<max){
    if(a[i]%2==0){
      a[bp] = a[i]
      bp++;
    }
    i++;
  }
  
  while(bp<max){
    
    bp++;
  }
  
  for(i = 0; i<max; i++){
    printf("%i ", a[i]);
  }
  
printf("\n");
  
  
  
  
return 0;
}