#include <stdio.h>
#include <string.h>

#define MAX 20

void kopiraj(char s2[], char s1[]);
void spoji(char s2[], char s1[]);

void kopiraj(char s2[], char s1[]){
  int i = 0;
  for(i = 0;s1[i];i++){
    s2[i] = s1[i];
  }
  s2[i] = '\0';
}

void spoji(char s2[], char s1[]){
  int i = 0;
  for(i = 0;i<strlen(s1);i++){
    s2[strlen(s2)+i] = s1[i];
  }
}


int main(){
  char s1[MAX+1], s2[4*MAX+1];
  scanf("%s", s1);
  if(strlen(s1)>MAX){
    printf("-1\n");
    return -1;
  }
  
  kopiraj(s2, s1);
  spoji(s2, s1);
  spoji(s2, s1);
  spoji(s2, s1);
  s2[strlen(s2)+1] = '\0';  
  printf("%s\n", s2);
  
  
  
  return 0;
}