#include <stdio.h>

#define MAX 21

void kopiraj_n(char s[], char t[], int n);

void kopiraj_n(char s[], char t[], int n){
  int i = 0;
  for(i = 0;i<n;i++){
    t[i] = s[i];
  }
  t[i] = '\0';
}

int main(){
  char s[MAX], t[MAX];
  int n;
  scanf("%s", s);
  scanf("%i", &n);
  if(n>MAX-1 || n<1){
    printf("-1\n");
    return -1;
  }
  
  kopiraj_n(s, t, n);
  
  printf("%s\n", t);
  
  return 0;
}