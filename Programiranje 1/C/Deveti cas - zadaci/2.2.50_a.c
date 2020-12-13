#include <stdio.h>

int main(){
    
    int n, j = 1, i = 1;
    scanf("%i", &n);
    
    if(n<1){
        printf("-1\n");
        return -1;
    }
    
    while(i<=n){
        while(j<=n){
            printf("%3i", i*j);
            j++;
        }
        j = 1;
        printf("\n");
        i++;
    }
    
    
return 0;
}