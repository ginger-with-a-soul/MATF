#include <stdio.h>
#include <stdlib.h>

#define MAX 50

double suma_na_glavnoj(double mat[][MAX], int n);
double suma_na_sporednoj(double mat[][MAX], int n);
double suma_iznad(double mat[][MAX], int n);
double suma_ispod(double mat[][MAX], int n);

double suma_na_glavnoj(double mat[][MAX], int n){
  int j, k;
  double suma = 0;
  for(j = 0;j<n;j++){
    for(k = 0;k<n;k++){
      if(j==k){
        suma += mat[j][k];
      }
    }
  }
  return suma;
}

double suma_na_sporednoj(double mat[][MAX], int n){
  int j, k;
  double suma = 0;
  for(j = 0;j<n;j++){
    for(k = 0;k<n;k++){
      if(j+k==n-1){
        suma += mat[j][k];
      } 
    }
  }
  return suma;
}

double suma_iznad(double mat[][MAX], int n){
  int j, k;
  double suma = 0;
  for(j = 0;j<n;j++){
    for(k = j+1;k<n;k++){
      suma += mat[j][k];
    }
  }
  return suma;
}

double suma_ispod(double mat[][MAX], int n){
  int j, k;
  double suma = 0;
  for(j = 0;j<n;j++){
    for(k = 0;k<n;k++){
      if(j+k>=n){
        suma += mat[j][k];
      }
    }
  }
}

int main(){
  int j, k, n;
  double mat[MAX][MAX];
  scanf("%i", &n);
  
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(j = 0;j<n;j++){
    for(k = 0;k<n;k++){
      scanf("%lf", &mat[j][k]);
    }
  }
  
  printf("%.3lf\n%.3lf\n%.3lf\n%.3lf\n", suma_na_glavnoj(mat, n), suma_na_sporednoj(mat, n), suma_iznad(mat, n), suma_ispod(mat ,n));
  
  return 0;
}