#include <stdio.h>

#define max 100

int main(){
  int a[max], b[max];
  int n, i = 0, s = 0;
  scanf("%i", &n);
  
  if(n<1 || n>max){
    printf("-1\n");
    return -1;
  }
  
  while(i<n){
    scanf("%i", &a[i]);
    i++;
  }
  
  i = 0;
  
  while(i<n){
    scanf("%i", &b[i]);
    i++;
  }
  
  i = 0;
  
  while(i<n){
    s += a[i] * b[i];
    i++;
  }
  
  printf("%i\n", s);
return 0;  
}