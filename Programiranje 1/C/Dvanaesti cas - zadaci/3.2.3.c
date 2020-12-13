#include <stdio.h>

int presek(double k1, double k2, double n1, double n2, double *x, double *y);

int presek(double k1, double k2, double n1, double n2, double *x, double *y){
  if(k1==k2){
    return 0;
  }
  else{
    *x = (n2-n1)/(k1-k2);
    *y = k1*(*x) + n1;
    return 1;
  }
}

int main(){
  double n1, n2, k1, k2;
  double x, y;
  scanf("%lf %lf %lf %lf", &k1, &n1, &k2, &n2);
  
  if(presek(k1, k2, n1, n2, &x, &y)){
    printf("%.2lf %.2lf\n", x, y);
  }
  else{
    printf("0\n");
  }
  
  
  return 0;
}