#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 101

void skrati(char s[]);

void skrati(char s[]){
  int i = 0;
  for(i = strlen(s)-1;i>=0;i--){
    if(!isspace(s[i])){
      break;
    }
  }
  s[i+1] = '\0';
}

int main(){
  char s[MAX];
  fgets(s, MAX, stdin);
  
  printf("%s*\n", s);
  
  skrati(s);
  
  printf("%s*\n", s);
  
  return 0;
}