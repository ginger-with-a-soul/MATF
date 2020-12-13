#include <stdio.h>

#define MAX 50

int main(){
  
  unsigned n, k;
  int i = 0, j = 0, matrica[MAX][MAX], l, m, t, suma = 0, m1;
  
  scanf("%u", &n);
  
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    for(j = 0;j<n;j++){
      scanf("%i", &matrica[i][j]);
    }
  }
  
  scanf("%u", &k);
  
  if(k<1 || k>2*n-1){
    printf("-1\n");
    return -1;
  }
  
  t = k;
  
  for(;n-1>=0;--k){
    if(!k){
      l = n-t;
      m = 0;
      break;
    }
    if(n-1 == 0){
      t = k;
      for(;k;--k){
        if(!k){
          l = 0;
          m = t;
        }
      }
    }
  }
  
  for(;l<n;l++, m++){
    for(m1 = 0;m1<n;m1++){
      if(m1 == m){
        suma += matrica[l][m];
        printf("%i ", matrica[l][m]);
      }
    }
  }
  
  printf("\n%i\n", suma);
  
  return 0;
}