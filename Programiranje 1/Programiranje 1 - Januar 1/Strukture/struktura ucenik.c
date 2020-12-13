#include <stdio.h>

#define MAX_UCENIKA 30
#define MAX_IME 21

typedef struct ucenik{
  char ime[MAX_IME];
  int ocena1;
  int ocena2;
  int ocena3;
  int ocena4;
  int ocena5;
  int ocena6;
  int ocena7;
  int ocena8;
  int ocena9;
}ucenik;

int main(){
  ucenik ucenici[MAX_UCENIKA];
  int i = 0, n, m = 0, nedovoljni[MAX_UCENIKA], odlicni[MAX_UCENIKA], j = 0;
  float prosek;
  while((scanf("%s %i %i %i %i %i %i %i %i %i", ucenici[i].ime, &ucenici[i].ocena1, &ucenici[i].ocena2, &ucenici[i].ocena3, &ucenici[i].ocena4, &ucenici[i].ocena5, &ucenici[i].ocena6, &ucenici[i].ocena7, &ucenici[i].ocena8, &ucenici[i].ocena9)) != EOF){
    if(ucenici[i].ocena1 < 1 || ucenici[i].ocena1 > 5 || ucenici[i].ocena2 < 1 || ucenici[i].ocena2 > 5 || ucenici[i].ocena3 < 1 || ucenici[i].ocena3 > 5 || ucenici[i].ocena4 < 1 || ucenici[i].ocena4 > 5 || ucenici[i].ocena5 < 1 || ucenici[i].ocena5 > 5 || ucenici[i].ocena6 < 1 || ucenici[i].ocena6 > 5 || ucenici[i].ocena7 < 1 || ucenici[i].ocena7 > 5 || ucenici[i].ocena8 < 1 || ucenici[i].ocena8 > 5 || ucenici[i].ocena9 < 1 || ucenici[i].ocena9 > 5 ){
      printf("-1\n");
      return -1;
    }
    i++;
  }
  
  n = i;
  
  for(i = 0;i<n;i++){
    if(ucenici[i].ocena1 == 1 || ucenici[i].ocena2 == 1 || ucenici[i].ocena3 == 1 || ucenici[i].ocena4 == 1 || ucenici[i].ocena5 == 1 || ucenici[i].ocena6 == 1 || ucenici[i].ocena7 == 1 || ucenici[i].ocena8 == 1 || ucenici[i].ocena9 == 1){
      nedovoljni[m++] = i;
    }
    else{
      prosek = ucenici[i].ocena1 + ucenici[i].ocena2 + ucenici[i].ocena3 + ucenici[i].ocena4 + ucenici[i].ocena5 + ucenici[i].ocena6 + ucenici[i].ocena7 + ucenici[i].ocena8 + ucenici[i].ocena9;
      prosek = (float)prosek/9;
      if(prosek >= 4.5){
        odlicni[j++] = i;
      }
    }
  }
  
  for(i = 0;i<m;i++){
    printf("%s\n", ucenici[nedovoljni[i]].ime);
  }
  printf("................................................\n");
  for(i = 0;i<j;i++){
    printf("%s\n", ucenici[odlicni[i]].ime);
  }

  return 0;
}