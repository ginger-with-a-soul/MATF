#include <stdio.h>
#include <math.h>

int main(){
  int n, suma = 0, i = 0, m, nn, niz[30], ab = 1;
  double as;
  
  scanf("%i", &n);
  
  if(n<0){
    ab = -1;
  }
  n = ab*n;
  
  nn = n;
  for(i = 0;n;i++){
    m = n%10;
    suma += m;
    n /= 10;
  }
  
  as = (double)suma/i;
  
  for(i = 0;nn;){
    m = nn%10;
    if(m<=as){
      niz[i++] = m;
    }
    nn /= 10;
  }
  n = 0;
  for(m = 0;m<i;m++){
    n += niz[m]*pow(10, m);
  }
  
  printf("%i\n", ab*n);
  
  return 0;
}