#include <stdio.h>
#include <string.h>

#define MAX_IME 21
#define MAX_PREZIME 31
#define MAX 50
#define MAX_EMAIL 51

typedef struct osoba{
  char ime[MAX_IME];
  char prezime[MAX_PREZIME];
  char email[MAX_EMAIL];
}osoba;

int main(){
  
  unsigned n, i = 0;
  osoba osobe[MAX];
  
  scanf("%u", &n);
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    scanf("%s %s %s", osobe[i].ime, osobe[i].prezime, osobe[i].email);
  }
  
  for(i = 0;i<n;i++){
    if(strstr(osobe[i].email, "@gmail.com")){
      printf("%s %s\n", osobe[i].ime, osobe[i].prezime);
    }
  }
  
  
  return 0;
}