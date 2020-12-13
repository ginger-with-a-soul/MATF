#include <stdio.h>

float razlomljeni_deo(float);

float razlomljeni_deo(float a){
return a-(int)a;  
}

int main(){
  float x;
  scanf("%f", &x);
  x = x<0? -x : x;
  printf("%.4f\n", razlomljeni_deo(x));
return 0;  
}