#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 21

void ukloni(char s[]);


void ukloni(char s[]){
  int i = 0, n = 0;
  for(i = 0;s[i];i++){
    if(!(isupper(s[i]) || islower(s[i]))){
      s[n++] = s[i];
    }
  }
  s[n] = '\0';
}

int main(){
  char s[MAX];
  scanf("%s", s);
  if(strlen(s)>MAX-1 || strlen(s)<1){
    printf("-1\n");
    return -1;
  }
  
  ukloni(s);
  printf("%s\n", s);
  
  return 0;
}