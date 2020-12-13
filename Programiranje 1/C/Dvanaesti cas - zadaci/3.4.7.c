#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void prosek_vrste(int mat[][MAX], int n, int m, double niz[n]);

void prosek_vrste(int mat[][MAX], int n, int m, double niz[n]){
  int suma = 0, j, k, i = 0;
  double prosek;

  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      suma += mat[j][k];
    }
    prosek = (double)suma/m;
    niz[i++] = prosek;
    suma = 0;
  }
  for(i = 0;i<n;i++){
    printf("%.1lf ", niz[i]);
  }
  printf("\n");
}

int main(){
  int mat[MAX][MAX], n, m, j, k;

  scanf("%i %i", &n, &m);
  if(n<1 || m<1 || n>MAX || m>MAX){
    printf("-1\n");
    return -1;
  }
  
  double niz[n];
  
  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      scanf("%i", &mat[j][k]);
    }
  }
  
  prosek_vrste(mat, n, m, niz);
  
  return 0;
}