#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int main(){
  int mat[MAX][MAX];
  int n, m, j = 0, k = 0;
  scanf("%i %i", &n, &m);
  if(n<1 || n>MAX || m<1 || m>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      scanf("%i", &mat[j][k]);
    }
  }
  
  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      printf("%i ", mat[j][k]);
    }
    printf("\n");
  }
  
  
  return 0;
}