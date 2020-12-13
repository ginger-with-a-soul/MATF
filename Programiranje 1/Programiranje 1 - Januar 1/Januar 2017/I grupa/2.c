#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 21

int main(){
  
  char s1[MAX], s2[] = "programiranje";
  for(;scanf("%s", s1) != EOF;){
    if(strcasestr(s2, s1) != NULL){
      printf("\n%s\n", s1);
    }
  }
  
  
  return 0;
}