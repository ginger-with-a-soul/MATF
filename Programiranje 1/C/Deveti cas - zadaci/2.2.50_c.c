#include <stdio.h>

int main(){
  
  int n, i = 1, j = 0;
  scanf("%i", &n);

 for(i = 1;i<=n;i++){
   for(j = 0;j<n;j++){
     if((j+i)%n==0){
      printf("%3i", n);
    }
    else{
      printf("%3i", (i+j)%n);
    }
   }
  j = 0;
  printf("\n");
}

return 0;
}