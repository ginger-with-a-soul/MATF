#include <stdio.h>


int main(){
  
  int n = 1, i = 0, m, br = 0, niz[br];
  
  scanf("%i", &n);
  
  do{

    m = n;
    for(i = 0;n;i++){
      n /= 10;
    }
    if(i%2){
      niz[br++] = m;
    }
    scanf("%i", &n);
    
  }while(n);
  
  for(i = 0;i<br;i++){
    printf("%i ", niz[i]);
  }
  
  printf("\n");
  
  
  
  return 0;
}