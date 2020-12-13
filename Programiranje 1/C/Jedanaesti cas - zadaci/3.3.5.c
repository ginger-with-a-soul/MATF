#include <stdio.h>
#include <ctype.h>

#define MAX 21

int main(){
  char s[MAX], c;
  int i = 0;
  scanf("%s %c", s, &c);
  for(i = 0;s[i];i++){
    if(s[i]==c){
      printf("%i\n", i);
      return 1;
    }
  }
  printf("-1\n");
  return 0;
}