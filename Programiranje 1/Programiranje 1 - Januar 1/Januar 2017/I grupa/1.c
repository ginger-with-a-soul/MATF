#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
  
  int n, m, t, aps, niz[21], j = 0;
  
  scanf("%i", &n);
  if(!n){
    printf("-1\n");
    return -1;
  }
  if(n<0){
    aps = -1;
  }
  else{
    aps = 1;
  }
  
  for(;n;){
    m = abs(n%10);
    if(m%2){
      niz[j++] = m;
    }
    n /= 10;
  }
  
  for(t = 0;t<j;t++){
    n += niz[t]*pow(10, t);
  }
  
  printf("%i\n", aps*n);
  
  
  return 0;
}