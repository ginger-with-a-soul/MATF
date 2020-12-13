#include <stdio.h>

#define MAX 50

void min_max(double* a, int n, double *min, double *max);

void min_max(double* a, int n, double *min, double *max){
  int i = 0;
  for(i = 0;i<n;i++){
    if(*min>a[i]){
     *min = a[i];
    }
    if(*max<a[i]){
      *max = a[i];
    }
  }
}

int main(){
  int n, i = 0;
  double a[MAX];
  scanf("%i", &n);
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  for(i = 0;i<n;i++){
    scanf("%lf", &a[i]);
  }
  double max = a[0], min = a[0];
  min_max(a, n, &min, &max);
  
  printf("%.3lf\n%.3lf\n", min, max);
  
  
  return 0;
}