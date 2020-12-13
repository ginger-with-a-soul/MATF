#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 102

void f3(char s[], char* c, int* br);

void f3(char s[], char* c, int* br){
  int i = 0, j = 0, max = 0, m = 0, ascii, min = 127;
  
  for(i = 0;i<=strlen(s);i++){
    for(j = 0;j<=strlen(s);j++){
      if(s[i]==s[j]){
        m++;
      }
    }
    ascii = (int)s[i];
    if(m>=max && ascii<=min){
      max = m;
      min = ascii;
      *c = s[i];
      *br = m;
    }
    m = 0;
  }
}
int main(){
  char s[MAX], c;
  int br = 0;
  fgets(s, MAX, stdin);
  f3(s, &c, &br);
  
  printf("\n%c %i\n", c, br);
  return 0;
}