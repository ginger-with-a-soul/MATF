#include <stdio.h>

#define MAX 11

int podniska(char s[], char t[]);

int podniska(char s[], char t[]){
  int i = 0, j = 0, e = 0, n = 0;
  for(i = 0;s[i];i++){
    for(j = 0;t[j];j++){
      if(t[j]==s[i]){
        e++;
      }
      
    }
    n = j;
    j = 0;
  }
  if(e>=n){
    return 1;
  }
  else{
    return 0;
  }
}

int main(){
  char s[MAX], t[MAX];
  scanf("%s %s", s, t);
  
  if(podniska(s, t)){
    printf("Da\n");
    return 1;
  }
  
  
  printf("Ne\n");
    
  return 0;
  
}