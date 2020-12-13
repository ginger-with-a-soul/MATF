#include <stdio.h>

#define MAX 21

void modifikacija(char s[]);

void modifikacija(char s[]){
  int i = 0;
  for(i = 0;s[i];i++){
    if(i%2){
      s[i] = '*';
    }
  }
}

int main(){
  char s[MAX];
  scanf("%s", s);
  
  modifikacija(s);
  
  printf("%s\n", s);
  
  return 0;
}