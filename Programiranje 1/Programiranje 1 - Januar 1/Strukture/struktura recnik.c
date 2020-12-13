#include <stdio.h>
#include <string.h>

#define MAX_PAROVA 100
#define MAX_DUZINA_RECENICE 100
#define MAX_REC 51

typedef struct ParReci{
  char sr[MAX_REC];
  char en[MAX_REC];
}ParReci;

void prevodjenje(ParReci recnik[], int n, char rec[], char prevod[]);

void prevodjenje(ParReci recnik[], int n, char rec[], char prevod[]){
  int i = 0;
  for(i = 0;i<n;i++){
    if(strcmp(recnik[i].sr, rec) == 0){
      strcpy(prevod, recnik[i].en);
      return;
    }
  }
  
  for(i = 0;rec[i];i++){
    prevod[i] = '*';
  }
  prevod[i] = '\0';
  return;
}

int main(){
  
  ParReci recnik[MAX_PAROVA];
  int i = 0, n;
  char c = ' ', rec[MAX_REC], prevod[MAX_REC];
  
  for(;(scanf("%s %s", recnik[i].sr, recnik[i].en)) != EOF;i++){
    if(i==MAX_PAROVA){
      break;
    }
  }
  
  n = i;
  
  for(;c!='\n';){
    scanf("%s", rec);
    prevodjenje(recnik, n, rec, prevod);
    printf("%s ", prevod);
    c = getchar();
  }
  
  printf("\n");
  
  return 0;
}