#include <stdio.h>

#define MAX 50

int main(){
  
  unsigned n, i, j, r, t;
  
  int matrica[MAX][MAX], suma = 0;;
  
  scanf("%u", &n);
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  scanf("%u", &i);
  scanf("%u", &j);
  if(i<0 || j>=n || j<0 || i>j){
    printf("-1\n");
    return -1;
  }
  
  for(r = 0;r<n;r++){
    for(t = 0;t<n;t++){
      scanf("%i", &matrica[r][t]);
    }
  }
  
  for(r = i;r<=j;r++){
    for(t = i;t<=j;t++){
      if(r==i || r==j || t==i || t==j){
        suma += matrica[r][t];
      }
    }
  }
  
  printf("%i\n", suma);
  
  
  return 0;
}