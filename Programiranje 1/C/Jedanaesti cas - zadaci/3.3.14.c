#include <stdio.h>

#define MAX 20

void dupliranje(char s[], char t[]);

void dupliranje(char s[], char t[]){
  int i = 0, j = 0;
  for(i = 0, j = 0;s[i];i++, j++){
    t[j++] = s[i];
    t[j] = s[i];
  }
  t[j] = '\0';
}

int main(){
  char s[MAX+1], t[2*MAX+1];
  scanf("%s", s);
  
  dupliranje(s, t);
  
  printf("%s\n", t);
  
  return 0;
}