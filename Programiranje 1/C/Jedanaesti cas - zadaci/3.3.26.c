#include <stdio.h>
#include <ctype.h>

#define MAX 21

void zameni_slova(char* s);

void zameni_slova(char* s){
  int i = 0;
  for(i = 0;s[i];i++){
    if(islower(s[i])){
      if(s[i]=='z'){
        s[i] = 'a';
      }
      else{
        s[i] += 1;
      }
    }
    else if(isupper(s[i])){
      if(s[i]=='Z'){
        s[i] = 'A';
      }
      else{
        s[i] += 1;
      }
    }
  }
}

int main(){
  char s[MAX];
  scanf("%s", s);
  
  zameni_slova(s);
  
  printf("%s\n", s);
  
  return 0;
}