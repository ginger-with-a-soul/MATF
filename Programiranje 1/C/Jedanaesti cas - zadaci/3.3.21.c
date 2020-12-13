#include <stdio.h>

#define MAX 21

char* strchr_klon(char* s, char c);

char* strchr_klon(char* s, char c){
  int i = 0;
  for(i = 0;s[i];i++){
    if(s[i]==c){
      return &s[i];
    }
    else{
      return NULL;
    }
  }
  
}

int main(){
  char s[MAX], c;
  scanf("%s %c", s, &c);
  
  if(strchr_klon(s, c)!=NULL){
    printf("1\n");
  }
  else{
    printf("-1\n");
  }
  
  
  
  return 0;
}