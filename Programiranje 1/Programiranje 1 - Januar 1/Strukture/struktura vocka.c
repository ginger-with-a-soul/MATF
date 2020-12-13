#include <stdio.h>
#include <string.h>

#define MAX_DUZINA 21
#define MAX_VOCKI 50

typedef struct vocka{
  char ime[MAX_DUZINA];
  float vitamin;
}vocka;

int main(){
  vocka vocke[MAX_VOCKI];
  char ime[MAX_DUZINA];
  int i = 0, max_vitamina = 0, n = 0;
  
  for(i = 0;i<MAX_VOCKI;i++){
    scanf("%s", ime);
    if(strcmp(ime, "KRAJ") == 0){
      break;
    }
    
    strcpy(vocke[i].ime, ime);
    
    scanf("%f", &vocke[i].vitamin);
  }
  
  for(n = 0;n<i;n++){
    if(vocke[n].vitamin>vocke[max_vitamina].vitamin){
      max_vitamina = n;
    }
  }
  
  printf("%s\n", vocke[max_vitamina].ime);
  
  
  
  return 0;
}