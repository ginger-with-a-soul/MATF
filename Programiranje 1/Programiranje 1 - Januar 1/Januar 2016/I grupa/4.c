#include <stdio.h>
#include <string.h>

#define MAX 999

typedef struct prevoz{
  char tip[10];
  int linija;
  int bp;
}prevoz;

int main(){
  
  int n, i = 0, bl, pm = 0;
  
  scanf("%i", &n);
  
  if(n<0 || n>MAX+1){
    printf("-1\n");
    return -1;
  }
  
  prevoz niz[MAX+1];
  
  for(i = 0;i<n;i++){
    scanf("%s %i %i", niz[i].tip, &niz[i].linija, &niz[i].bp);
    if((strcmp(niz[i].tip, "autobus") != 0) && (strcmp(niz[i].tip, "trolejbus") != 0) && (strcmp(niz[i].tip, "tramvaj") != 0)){
      printf("-1\n");
      return -1;
    }
    if(niz[i].linija > MAX || niz[i].linija < 0){
      printf("-1\n");
      return -1;
    }
    if(niz[i].bp < 0 || niz[i].bp > 30){
      printf("-1\n");
      return -1;
    }
    if((strcmp(niz[i].tip, "autobus") == 0) && niz[i].bp > 25){
      printf("-1\n");
      return -1;
    }
    if((strcmp(niz[i].tip, "trolejbus") == 0) && niz[i].bp > 20){
      printf("-1\n");
      return -1;
    }
    if((strcmp(niz[i].tip, "tramvaj") == 0) && niz[i].bp > 30){
      printf("-1\n");
      return -1;
    }
  }
  
  
  scanf("%i", &bl);
  
  for(i = 0;i<n;i++){
    if(bl==niz[i].linija){
      if(strcmp(niz[i].tip, "autobus") == 0){
        pm = 25 - niz[i].bp;
      }
      else if(strcmp(niz[i].tip, "trolejbus") == 0){
        pm = 20 - niz[i].bp;
      }
      else if(strcmp(niz[i].tip, "tramvaj") == 0){
        pm = 30 - niz[i].bp;
      }
    }
  }
  
  printf("%i\n", pm);
  
  return 0;
}