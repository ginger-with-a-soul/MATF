#include <stdio.h>

#define MAX 31
#define MAX_STUDENATA 2000

typedef struct student{
  char ime[MAX];
  char prezime[MAX];
  char smer;
  float prosek;
}student;

int main(){
  
  student studenti[MAX_STUDENATA];
  int i = 0;
  unsigned n;
  char smer1;
  float prosek1 = 6;
  
  scanf("%u", &n);
  
  if(n<1 || n>MAX_STUDENATA){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    scanf("%s %s %c %f", studenti[i].ime, studenti[i].prezime, &studenti[i].smer, &studenti[i].prosek);
    if((studenti[i].smer != 'R' && studenti[i].smer != 'I' && studenti[i].smer != 'V' && studenti[i].smer != 'N' && studenti[i].smer != 'T' && studenti[i].smer != 'O') || studenti[i].prosek < 6.0 || studenti[i].prosek > 10){
      printf("-1\n");
      return -1;
    }
  }
  getchar();
  scanf("%c", &smer1);
  if(smer1 != 'R' && smer1 != 'I' && smer1 != 'V' && smer1 != 'N' && smer1 != 'T' && smer1 != 'O'){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    if(smer1 == studenti[i].smer){
      printf("%s %s\n", studenti[i].ime, studenti[i].prezime);
    }
  }
  
  printf("................................................\n");
  
  for(i = 0;i<n;i++){
    if(studenti[i].prosek >= prosek1){
      prosek1 = studenti[i].prosek;
    }
  }
  
  for(i = 0;i<n;i++){
    if(studenti[i].prosek == prosek1){
      printf("%s %s\n", studenti[i].ime, studenti[i].prezime);
    }
  }
  
  return 0;
}