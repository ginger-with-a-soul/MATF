#include <stdio.h>

#define MAX 21

int samoglasnik_na_kraju(char s[]);

int samoglasnik_na_kraju(char s[]){
  int i = 0;
  for(i = 0;s[i];i++){
  }
  if(s[i-1]=='a' || s[i-1]=='e' || s[i-1]=='o' || s[i-1]=='i' || s[i-1]=='u'){
    return 1;
  }
  else{
    return 0;
  }
}

int main(){
  char s[MAX];
  scanf("%s", s);
  
  if(samoglasnik_na_kraju(s)){
    printf("Da\n");
  }
  else{
    printf("Ne\n");
  }
  
  return 0;
}