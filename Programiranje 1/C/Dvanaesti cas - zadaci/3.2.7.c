#include <stdio.h>
#include <ctype.h>

#define MAX 21

void malo_u_veliko(char s[], char t[], int *br);

void malo_u_veliko(char s[], char t[], int *br){
  int i = 0;
  for(i = 0;s[i];i++){
    if(islower(s[i])){
      t[i] = toupper(s[i]);
      (*br)++;
    }
    else{
      t[i] = s[i];
    }
  }
  t[i] = '\0';
}
int main(){
  char s[MAX], t[MAX];
  int br = 0;
  scanf("%s", s);
  
  malo_u_veliko(s, t, &br);
  
  printf("%s\n%i\n", t, br);
  
  
  
  return 0;
}