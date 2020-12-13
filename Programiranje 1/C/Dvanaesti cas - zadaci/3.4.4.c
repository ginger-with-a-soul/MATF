#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void transponat(int mat[][MAX], int n, int m);

void transponat(int mat[][MAX], int n, int m){
  int j = 0, k = 0;
  for(j = 0;j<m;j++){
    for(k = 0;k<n;k++){
      printf("%i ", mat[k][j]);
    }
    printf("\n");
  }
}

int main(){
  int n, m, j, k;
  int mat[MAX][MAX];
  scanf("%i %i", &n, &m);
  if(n<1 || m<1 || n>MAX || m>MAX){
    printf("-1\n");
    exit(EXIT_FAILURE);
  }
  
  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      scanf("%i", &mat[j][k]);
      printf("%i ", mat[j][k]);
    }
    printf("\n");
  }
  
  transponat(mat, n, m);
  
  return 0;
}