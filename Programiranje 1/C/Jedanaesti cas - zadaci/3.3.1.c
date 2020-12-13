#include <stdio.h>
#include <ctype.h>

#define MAX 11

void konvertuj(char s[]);

void konvertuj(char s[]){
  int i = 0;
  for(i = 0;s[i];i++){
    if(isupper(s[i])){
      s[i] = tolower(s[i]);
    }
    else if(islower(s[i])){
      s[i] = toupper(s[i]);
    }
  }
}

int main(){
  char s[MAX];
  scanf("%s", s);
  konvertuj(s);
  printf("%s\n", s);
  
  return 0;
}