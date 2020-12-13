#include <stdio.h>
#include <string.h>

#define MAX_IME 21
#define MAX_PRODAVNICA 50

typedef struct cenoteka{
  char ime[MAX_IME];
  float cena;
}cenoteka;

int main(){
  cenoteka prodavnica[MAX_PRODAVNICA];
  int n, i = 0;
  float cena1;
  scanf("%i", &n);
  if(n<0 || n>49){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    scanf("%s %f", prodavnica[i].ime, &prodavnica[i].cena);
  }
  
  scanf("%f", &cena1);
  
  for(i = 0;i<n;i++){
    if(prodavnica[i].cena <= cena1){
      printf("%s\n", prodavnica[i].ime);
    }
  }
  
  return 0;
}