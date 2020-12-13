#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void ucitaj(int mat[][MAX], int *n, int *m);

void ispisi(int mat[][MAX], int n, int m);

void ucitaj(int mat[][MAX], int *n, int *m){
  scanf("%i %i", n, m);
  int j, k;
  if(*n<1 || *m<1 || *n>MAX || *m>MAX){
    printf("-1\n");
    exit(EXIT_FAILURE);
  }
  for(j = 0;j<(*n);j++){
    for(k = 0;k<(*m);k++){
      scanf("%i", &mat[j][k]);
    }
  }
}

void ispisi(int mat[][MAX], int n, int m){
  int j = 0, k = 0;
  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      printf("%i ", mat[j][k]);
    }
    printf("\n");
  }
}

int main(){
  int mat[MAX][MAX];
  int n, m;
  ucitaj(mat, &n, &m);
  ispisi(mat, n, m);

  return 0;
}