#include <stdio.h>

#define MAX 100

int main(){
  
  int niz[MAX], i = 0, n, k, pp, s;
  
  scanf("%i", &n);
  if(n%2 == 0 || n<1){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    scanf("%i", &niz[i]);
  }
  
  scanf("%i", &k);
  
  if(k>n/2 || k<1){
    printf("-1\n");
    return -1;
  }
  
  pp = n/2;
  s = 1;
  for(i = 0;i<k;i++){
    printf("%i ", niz[pp-(s++)]);
  }
  s = 1;
  for(i = 0;i<k;i++){
    printf("%i ", niz[pp+s++]);
  }
  
  return 0;
}