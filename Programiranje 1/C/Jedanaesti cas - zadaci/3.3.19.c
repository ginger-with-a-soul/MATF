#include <stdio.h>
#include <string.h>

#define MAX 81

int ucitaj_liniju(char s[], int n){
  int i = 0;
  int c;
  while((c = getchar())!='\n' && c!=EOF && i<n-2){
    s[i] = c;
    i++;
  }
  s[i] = '\n';
  s[i+1] = '\0';
  
  return i;
}


int main(){
  
  char s[MAX], najduza_linija[MAX];
  int max = 0, duzina;
  
  while((duzina = ucitaj_liniju(s, MAX))>0){
    if(duzina>max){
      max = duzina;
      strcpy(najduza_linija, s);
    }
  }
  
  printf("\n%s%i\n", najduza_linija, max);
  
  
  return 0;
}