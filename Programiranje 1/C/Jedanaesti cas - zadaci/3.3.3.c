#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 21

int poredi(char s1[], char s2[]);

int poredi(char s1[], char s2[]){
  int i = 0;
  if(strlen(s1)!=strlen(s2)){
    return 0;
  }
  for(i = 0;s1[i];i++){
    s1[i] = tolower(s1[i]);
    s2[i] = tolower(s2[i]);
    if(s1[i]!=s2[i]){
      return 0;
    }
  }
  return 1;
}

int main(){
  char s1[MAX], s2[MAX];
  scanf("%s %s", s1, s2);
  
  if(poredi(s1, s2)){
    printf("Iste su\n");
  }
  else{
    printf("Nisu iste\n");
  }
  return 0;
}