#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

int main(){
  int i = 0, j = 0, a, cifra = 0, max = 0;
  char s[MAX], s1[MAX];

  
  do{
    scanf("%s", s);
    a = strlen(s);
    
    for(i = 0;i<a;i++){
      if(isdigit(s[i])){
        cifra++;
      }
    }
    if(cifra>max){
      max = cifra;
      strcpy(s1, s);
    }
    cifra = 0;
    
  }while((strcmp(s, "KRAJ") != 0));
  
  
  if(max>0){
    printf("%s\n", s1);
  }
  else{
    printf("-1\n");
  }

return 0;
}