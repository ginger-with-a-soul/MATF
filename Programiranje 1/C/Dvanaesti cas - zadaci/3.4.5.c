#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void razmeni(int mat[][MAX], int n, int m, int j1, int j2);

void razmeni(int mat[][MAX], int n, int m, int j1, int j2){
  int j = 0, k = 0, i = 0;
  
  for(j = 0;j<n;j++){
    if(j!=j1 && j!=j2){
      for(k = 0;k<m;k++){
        printf("%i ", mat[j][k]);
      }
      printf("\n");
    }
    else if(j==j1){
      i = j2;
      for(k = 0;k<m;k++){
        printf("%i ", mat[i][k]);
      }
      printf("\n");
    }
    else{
      i = j1;
      for(k = 0;k<m;k++){
        printf("%i ", mat[i][k]);
      }
      printf("\n");
    }
  }
  
}

int main(){
  int mat[MAX][MAX], j1, j2, n, m, j, k;
  
  scanf("%i %i", &n, &m);
  
  if(n<1 || m<1 || n>MAX || m>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      scanf("%i", &mat[j][k]);
    }
  }
  
  scanf("%i %i", &j1, &j2);
  
  if(j1<0 || j2<0 || j1>n || j2>n){
    printf("-1\n");
    return -1;
  }
  
  razmeni(mat, n, m, j1, j2);
  
  return 0;
}