#include <stdio.h>

int main(){
  
  int n, max = 0, min = 0, razlika;
  scanf("%i", &n);
  if(n<0 || n==0){
    printf("-1\n");
    return -1;
  }
  max = n;
  min = n;
  
  while(scanf("%i", &n)){
    if(n<0){
      printf("-1\n");
      return -1;
    }
    if(n==0){
      break;
    }
    if(n>=max){
      max = n;
    }
    if(n<=min){
      min = n;
    }
  }
  
  razlika = (max-min)*(max-min);
  
  printf("\n%i\n", razlika);
  
  return 0;
}