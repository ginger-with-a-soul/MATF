#include <stdio.h>

#define MAX_IME 21
#define MAX_GRADOVA 50

typedef struct grad{
  char ime[MAX_IME];
  float temperatura;
}grad;

int main(){
  int n, i = 0;
  scanf("%i", &n);
  if(n<1 || n>MAX_GRADOVA){
    printf("-1\n");
    return -1;
  }
  
  grad gradovi[n];
  
  for(i = 0;i<n;i++){
    scanf("%s %f", gradovi[i].ime, &gradovi[i].temperatura);
  }
  
  for(i = 0;i<n;i++){
    if(gradovi[i].temperatura>=3 && gradovi[i].temperatura<=8){
      printf("%s\n", gradovi[i].ime);
    }
  }
  
  return 0;
}