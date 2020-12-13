#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void indeks_zbira_susednih(int mat[][MAX], int n, int m);

void indeks_zbira_susednih(int mat[][MAX], int n, int m){
  int j, k;
  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      if(mat[j][k]==mat[j-1][k-1] + mat[j-1][k] + mat[j-1][k+1] + mat[j][k-1] + mat[j][k+1] + mat[j+1][k-1] + mat[j+1][k] + mat[j+1][k+1]){
        printf("%i %i\n", j, k);
      }
    }
  }
  
  
}

int main(){
  int mat[MAX][MAX], j, k, n, m;
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
  
  indeks_zbira_susednih(mat, n, m);
  
  return 0;
}
  