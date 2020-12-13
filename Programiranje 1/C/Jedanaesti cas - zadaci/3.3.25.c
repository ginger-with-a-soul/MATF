#include <stdio.h>
#include <string.h>

#define MAX 21

void rotiraj(char* s, int k);

void rotiraj(char* s, int k){
  int i = 0, j = 0, prvi_element;
 
  for(i = 0;i<k;i++){
     prvi_element = s[0];
     for(j = 0;s[j];j++){
       s[j] = s[j+1];
    }
    s[strlen(s)] = prvi_element;
  }
  s[strlen(s)+1] = '\0';
}

int main(){
  char s[MAX];
  int k;
  scanf("%s %i", s, &k);
  
  rotiraj(s, k);
  
  printf("%s\n", s);
  
  return 0;
}