#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50


int main(){
  double suma = 0, rez;
  int n, m, j, k;
  int mat[MAX][MAX];
  scanf("%i %i", &n, &m);
  if(n<1 || m<1 || n>MAX || m>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(j = 0;j<n;j++){
    for(k = 0;k<m;k++){
      scanf("%i", &mat[j][k]);
      suma += mat[j][k]*mat[j][k];
    }
  }
  rez = sqrt(suma);
  printf("%.3lf\n", rez);
  
  
  return 0;
}