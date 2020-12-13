#include <stdio.h>

#define MAX 50

int main(){
  
  int i = 0, j = 0, matrica[MAX][MAX], suma = 0, n;
  double ars;
  
  scanf("%i", &n);
  
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    for(j = 0;j<n;j++){
      scanf("%i", &matrica[i][j]);
      suma += matrica[i][j];
    }
  }
  
  ars = (double)suma/(n*n);
  suma = 0;
  
  for(i = 0;i<n;i++){
    for(j = 0;j<n;j++){
      if(i==j && matrica[i][j]<ars){
        printf("%i ", matrica[i][j]);
        suma++;
      }
    }
  }
  
  for(i = 0;i<n;i++){
    for(j = 0;j<n;j++){
      if(j+i==n-1 && matrica[i][j]<ars){
        printf("%i ", matrica[i][j]);
        suma++;
      }
    }
  }
  printf("\n");
  if(!suma){
    printf("Nema\n");
    return -1;
  }
  
  
  
  return 0;
}