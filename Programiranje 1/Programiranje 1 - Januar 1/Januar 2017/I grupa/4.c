#include <stdio.h>
#include <string.h>

#define MAX 51

typedef struct karta{
  char znak[5];
  unsigned broj;
}karta;

int main(){
  
  int i = 0, n, br = 0;
  
  karta spil[MAX];
  
  scanf("%u", &n);
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    scanf("%s %u", spil[i].znak, &spil[i].broj);
    if((strcmp(spil[i].znak, "karo") && strcmp(spil[i].znak, "tref") && strcmp(spil[i].znak, "pik") && strcmp(spil[i].znak, "herc")) || spil[i].broj < 1 || spil[i].broj > 14){
      printf("-1\n");
      return -1;
    }
    
  }
  
  scanf("%s %u", spil[n].znak, &spil[n].broj);
  
  if((strcmp(spil[n].znak, "karo") && strcmp(spil[n].znak, "tref") && strcmp(spil[n].znak, "pik") && strcmp(spil[n].znak, "herc")) || spil[n].broj < 1 || spil[n].broj > 14){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    if(strcmp(spil[i].znak, spil[n].znak) == 0 || spil[n].broj == spil[i].broj){
      printf("%s %u\n", spil[i].znak, spil[i].broj);
      br++;
    }
  }
  
  if(br){
    return 0;
  }
  else{
    printf("-1\n");
    return -1;
  }
  
  return 0;
}