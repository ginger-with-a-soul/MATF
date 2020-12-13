#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 81

int ucitaj_liniju(char s[], int n);
void br_velikih_i_malih(char s[], int *br_velikih, int *br_malih, int n, int duzina);

int ucitaj_liniju(char s[], int n){
  int i = 0;
  int c;
  
  while((c = getchar())!='.' && i<n-2 && c!=EOF){
    s[i] = c;
    i++;
  }
  s[i] = '\n';
  s[i+1] = '\0';
  
  return i;
}

void br_velikih_i_malih(char s[], int *br_velikih, int *br_malih, int n, int duzina){
  int i = 0;
  for(i = 0;i<duzina;i++){
    if(isupper(s[i])){
      (*br_velikih)++;
    }
    else if(islower(s[i])){
      (*br_malih)++;
    }
    
  }
}


int main(){
  char s[MAX], max_linija[MAX];
  int br_malih = 0, br_velikih = 0, razlika1, razlika2, n = MAX, duzina;
  
  while((duzina = ucitaj_liniju(s, n))>0){
    br_velikih_i_malih(s, &br_velikih, &br_malih, n, duzina);
    razlika2 = abs(br_velikih - br_malih);
    
    if(razlika2>razlika1){
      razlika1 = razlika2;
      strcpy(max_linija, s);
    }
  }
  
  printf("\n%s", max_linija);
  
  
  return 0;
}