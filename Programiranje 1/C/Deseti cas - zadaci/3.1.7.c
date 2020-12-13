#include <stdio.h>

#define max 100

int main(){
  int a[max], b[max], c[2*max], n, i = 0, k = 0;
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
  
  while(i<2*n){
    c[i++] = a[k];
    c[i] = b[k];
    i++;
    k++;
  }
  i = 0;
  
  while(i<2*n){
    printf("%i ", c[i]);
    i++;
  }
  printf("\n");
return 0;
}