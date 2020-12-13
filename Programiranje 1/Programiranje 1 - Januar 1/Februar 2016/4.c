#include <stdio.h>

#define MAX 100

int main(){
  int n, m, i = 0, j = 0, br = 0, l1, l2, k1, k2;
  char matrica[MAX][MAX];
  
  scanf("%i %i", &n, &m);
  if(n<1 || m<1 || n>MAX || m>MAX){
    printf("-1\n");
    return -1;
  }
  getchar();
  for(i = 0;i<n;i++){
    for(j = 0;j<m;j++){
      scanf("%c", &matrica[i][j]);
      if(matrica[i][j] != 'X' && matrica[i][j] != '-'){
        printf("-1\n");
        return -1;
      }
      getchar();
    }
  }
  
  scanf("%i %i", &l1, &l2);
  if(l1<0 || l2<0 || l1>=n || l2>=m){
    printf("-1\n");
    return -1;
  }
  scanf("%i %i", &k1, &k2);
  if(k1<l1 || k1>=n || k2>=m || k2<l2){
    printf("-1\n");
    return -1;
  }
  
  for(i = l1;i<=k1;i++){
    for(j = l2;j<=k2;j++){
      if(matrica[i][j]=='X'){
        br++;
      }
    }
  }
  
  printf("\n%i\n", br);
  
  return 0;
}