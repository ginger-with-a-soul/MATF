#include <stdio.h>
#include <ctype.h>

#define MAX 21

int main(){
  char s[MAX];
  scanf("%s", s);
  int i = 0;
  for(i = 0;s[i];i++){
    if(isupper(s[i])){
      printf("Da\n");
      return 1;
    }
    
  }
  
  printf("Ne\n");
  
  return 0;
}