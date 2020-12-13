#include <stdio.h>

#define MAX 100

int main(){
  int n, a[MAX], j = 0, novo_j = 0, i = 0;
  scanf("%i", &n);
  if(n<1 || n>100){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    scanf("%i", &a[i]);
    
  }
  
  for(i = 0, j = 0;i<n;i++){
    if(a[i]%10==0 || (a[i]%(a[i]%10)==0)){
      a[j++] = a[i];
  }
}
novo_j = j;
for(j = 0;j<novo_j;j++){
  printf("%i ", a[j]);
}
printf("\n");
return 0;
}