#include<stdio.h>

int f(int x){
  x--; 
  printf("%d", x);
  return --x;
  
}
int main(){
	int x;
	x=6;
	f(x);
	printf("%d", x);
	return 0;
}