#include <stdio.h>

#define max 100

int main(){
  int n, i = 0, a[max];
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
    if(i%2==0){
      printf("%i ", a[i]);
    }
    i++;
  }
  printf("\n");
  i = 0;
  while(i<n){
    if(a[i]%2==0){
      printf("%i ", a[i]);
    }
    i++;
  }
  printf("\n");
return 0;
}