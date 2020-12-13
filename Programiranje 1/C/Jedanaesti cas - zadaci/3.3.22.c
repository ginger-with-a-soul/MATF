#include <stdio.h>

#define MAX 21

int sprstn_klon(char* s, char* t);

int sprstn_klon(char* s, char* t){
  int i = 0, j = 0, br = 0;
  for(i = 0;s[i];i++){
    for(j = 0;t[j];j++){
      if(s[i]==t[j]){
        br++;
      }
    }
    j = 0;
  }
  return br;
}

int main(){
  char s[MAX], t[MAX];
  scanf("%s %s", s, t);
  
  printf("%i\n", sprstn_klon(s, t));
  
  return 0;
}