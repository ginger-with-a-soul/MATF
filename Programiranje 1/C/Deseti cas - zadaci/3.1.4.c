#include <stdio.h>

#define max 100

int main(){
  int a[max], b[max], i = 0, x, y;
  scanf("%i %i", &x, &y);
  x = x<0? -x : x;
  y = y<0? -y : y;
  
  while(i<max){
    a[i] = 0;
    b[i] = 0;
    i++;
  }
  i = 0;
  
  while(x!=0){
    i = x%10;
    a[i]++;
    x /= 10;
  }
  i = 0;
  
  while(y!=0){
    i = y%10;
    b[i]++;
    y /= 10;
  }
  i = 0;
  while(i<10){
    if((a[i]!=0 && b[i]!=0) || (a[i]==0 && b[i]==0)){
      i++;
      continue;
    }
    else{
      printf("Brojevi se ne zapisuju istim ciframa!\n");
      return -1;;
    }
  }
  printf("Brojevi se zapisuju istim ciframa!\n");
  
  
return 0;
}