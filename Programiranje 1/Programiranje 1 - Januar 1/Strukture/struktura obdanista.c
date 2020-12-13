#include <stdio.h>
#include <string.h>

#define MAX_DECE 200

typedef struct dete{
  char pol;
  unsigned godina;
  unsigned ocena;
}dete;

int main(){
  
  dete deca[MAX_DECE];
  unsigned i = 0, age, ukupna_ocena = 0, n, br = 0;
  char sex;
  float prosecna_ocena;
  
  scanf("%u", &n);
  if(n<1 || n>MAX_DECE){
    printf("-1\n");
    return -1;
  }
  
  
  for(i = 0;i<n;i++){
    getchar();
    scanf("%c", &deca[i].pol);
    if((deca[i].pol != 'm') && (deca[i].pol != 'z')){
      printf("-1\n");
      return -1;
    }
    
    scanf("%u", &deca[i].godina);
    if(deca[i].godina < 3 || deca[i].godina > 6){
      printf("-1\n");
      return -1;
    }
    scanf("%u", &deca[i].ocena);
    if(deca[i].ocena < 1 || deca[i].ocena > 5){
      printf("-1\n");
      return -1;
    }
  }
  
  getchar();
  
  scanf("%c %u", &sex, &age);
  if((sex != 'm' && sex != 'z') || age < 3 || age > 6){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    if(sex == deca[i].pol && age == deca[i].godina){
      ukupna_ocena += deca[i].ocena;
      br++;
    }
  }
  
  prosecna_ocena = (float)ukupna_ocena/br;
  
  printf("%.3f\n", prosecna_ocena);
  return 0;
}