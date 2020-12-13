#include <stdio.h>

#define max 100

int main(){
  int a[max], b[max], c[2*max], i = 0, n, k = 0;
  scanf("%i", &n);
  if(n<1 || n>max){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0; i<n; i++){
    scanf("%i", &a[i]);
  }
  
  for(i = 0; i<n; i++){
    scanf("%i", &b[i]);
  }
  
  for(i = 0; i<n; i++, k++){
    c[i] = b[k];
  }
  
  for(k = 0;i<2*n; i++, k++){
    c[i] = a[k];
  }
  
  for(i = 0; i<2*n; i++){
    printf("%i ", c[i]);
  }
  printf("\n");
  
return 0;
}