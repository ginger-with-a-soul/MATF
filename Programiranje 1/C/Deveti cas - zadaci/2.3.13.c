#include <stdio.h>

int sadrzi(int, int);
int sadrzi(int x, int c){
  while(x!=0){
    if(x%10==c){
      return 1;
    }
    x /= 10;
  }
return 0;
}

int main(){
  int x, c;
  scanf("%i %i", &x, &c);
  x = x<0? -x : x;
  if(c<0 || c>9){
    printf("-1\n");
    return -1;
  }
  printf("%i\n", sadrzi(x, c));
return 0;  
}