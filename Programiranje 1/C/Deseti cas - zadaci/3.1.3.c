#include <stdio.h>

#define max 100

int main(){
  int n, m[max], kn, i = 0;
  scanf("%i", &n);
  kn = n;
  n = n<0? -n : n;
  
  while(i<max){
    m[i] = 0;
    i++;
  }
  
  while(n!=0){
    i = n%10;
    m[i]++;
    n /= 10;
  }
  i = 0;
  while(i<10){
    if(m[i]){
      printf("U zapisu broja %i , cifra %i se pojavljuje %i puta\n", kn, i, m[i]);
    }
    i++;
  }
  
  
return 0;
}