#include <stdio.h>
#include <stdlib.h>

#define MAX_IME 21
#define MAX_STADION 31
#define MAX 1000
#define MIN 1
typedef struct DUEL{
  char imeGosta[MAX_IME];
  char imeDomacina[MAX_IME];
  char stadion[MAX_STADION];
  unsigned golDomacin;
  unsigned golGost;
}DUEL;

int main(){
  
  unsigned n, i = 0, m;
  int aps_razlika = 0;
  scanf("%u", &n);
  if(n<MIN || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  DUEL dueli[MAX];
  getchar();
  for(i = 0;i<n;i++){
    gets(dueli[i].imeDomacina);
    gets(dueli[i].imeGosta);
    gets(dueli[i].stadion);
    scanf("%u", &dueli[i].golDomacin);
    scanf("%u", &dueli[i].golGost);
    getchar();
    if(dueli[i].golDomacin<0 || dueli[i].golGost<0){
      printf("-1\n");
      return -1;
    }
    if(abs(dueli[i].golDomacin - dueli[i].golGost)>=aps_razlika){
      aps_razlika = abs(dueli[i].golDomacin - dueli[i].golGost);
      m = i;
    }
  }
  
  printf("%s\n", dueli[m].stadion);
  
  return 0;
}