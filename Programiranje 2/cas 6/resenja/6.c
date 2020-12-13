#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define KOEFS 11
#define EPS 0.0001
void greska()
{
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

// Racunanje vrednosti polinoma zadatog koeficijentima c u tacki x
// koriscenjem Hornerove seme
float vrednost(float* c, float x)
{
    float rez = 0;
    int i;
    for(i=KOEFS-1; i>=0; i--)
        rez = rez*x + c[i];
    return rez;
}

/*
 * Funkcija koja racuna nulu polinoma
 * c[0] + c[1]x + c[2]x^2 + .... + c[10]*x^10
 * metodom polovljenja intervala. 
 */
float nula(float* c, float levo, float desno)
{
    if(levo > desno)
        greska();
    
    float s = levo + (desno-levo)/2;
    float vr = vrednost(c, s);
    if(fabs(vr) < EPS)
        return s;
    else 
    {
        float levi_kraj = vrednost(c, levo);
        
        if(vr*levi_kraj < 0)
            return nula(c, levo, s);
        else
            return nula(c, s, desno);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
        greska();
    
    float a = atof(argv[1]);
    float b = atof(argv[2]);
    
    if(a > b)
        greska();
    
    int n = KOEFS;
    float c[KOEFS];
    
    int i;
    for(i=0; i<n; i++)
    {
        scanf("%f", &c[i]);
    }
    
    printf("%.2f\n", nula(c, a, b));
    
    return 0;
}