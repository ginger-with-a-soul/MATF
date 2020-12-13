#include <stdio.h>
#include <stdlib.h>

#define MAX_IME 51

void greska()
{
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    int n;
    scanf("%d", &n);
    if(n <= 0 || n > 100)
        greska();
    
    int i, j;
    FILE* fajl;
    char ime_fajla[MAX_IME];
    
    for(i=1; i<=n; i++)
    {
        /* Formiramo ime fajla kao i.txt */
        sprintf(ime_fajla, "%d.txt", i);
        
        /*Otvaramo fajl za pisanje*/
        fajl = fopen(ime_fajla, "w");
        if(fajl == NULL)
          greska();
        
        /* U fajl upisujemo vrednosti [0,n], sa korakom i */
        for(j=0; j<=n; j+=i)
        {
            fprintf(fajl, "%d ", j);
        }
        fprintf(fajl, "\n");
        
        /* Zatvaramo fajl i.txt */
        fclose(fajl);    
    }
    
    return 0;
}
