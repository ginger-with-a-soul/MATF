#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 10

int znak_broja(char s[]);
int niska_u_broj(char s[]);

int znak_broja(char s[]){
  if(s[0]=='-'){
    return -1;
  }
  else if(s[0]=='+'){
    return +1;
  }
  return 1;
}

int niska_u_broj(char s[]){
  int n = 0, i = 0;
  if(znak_broja(s)==-1 || znak_broja(s)==+1){
    i = 1;
  }
  for(i;s[i];i++){
    if(!(isdigit(s[i]))){
      break;
    }
    n = n*10 + (s[i] - '0');
  }
  n *= znak_broja(s);
  
  return n;
}


int main(){
  char s[MAX];
  scanf("%s", s);
  
  printf("%i\n", niska_u_broj(s));
  printf("%i\n", atoi(s));
  
  return 0;
}