#include <stdio.h>
#include <string.h>

#define MAX 30

int main(){
  char src[MAX+1], dst[3*MAX+1];
  scanf("%s", src);
  
  strcpy(dst, src);
  strcat(dst, src);
  strcat(dst, src);
  
  printf("%s\n", dst);
  
  return 0;
}