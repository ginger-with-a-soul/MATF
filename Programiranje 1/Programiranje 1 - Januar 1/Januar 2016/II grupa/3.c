#include <stdio.h>

#define MAX 100

int main(){
  
  int m, n, i = 0, j = 0;
  double matrica[MAX][MAX];
  
  scanf("%i %i", &n, &m);
  
  double ns[n], suma = 0;
  
  if(n<1 || m<1 || n>MAX || m>MAX){
    printf("-1\n");
    return -1;
  }

  for(i = 0;i<n;i++){
    for(j = 0;j<m;j++){
      scanf("%lf", &matrica[i][j]);
      suma += matrica[i][j];
      ns[i] = (double)suma/m;
    }
    suma = 0;
  }
  
  for(i = 0;i<n;i++){
    suma += ns[i];
  }
  
  printf("%.4lf\n", suma);
  
  return 0;
}