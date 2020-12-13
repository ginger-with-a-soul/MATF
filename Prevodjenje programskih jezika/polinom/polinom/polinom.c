#include "polinom.h"

void dodaj_koeficijent(Polinom* p, float x){
  p->stepen++;
  if(p->stepen > MAXSTEPEN){
    fprintf(stderr, "Preveliki stepen polinoma!\n");
    exit(EXIT_FAILURE);
  }
    
  p->koeficijenti[p->stepen] = x;
}


void ispisi(const Polinom* p){
  int i;
  
  for(i=0; i<= p->stepen; i++ ){
    if( i == 0){
      if(p->koeficijenti[i] != 0 || p->stepen ==0 )
        printf("%g ",p->koeficijenti[i]);
      continue;
    }
    
    if(p->koeficijenti[i] != 0){
      if(p-> koeficijenti[i]>0){
        printf("+ ");
        
        if(p->koeficijenti[i] != 1)
          printf("%g ",p->koeficijenti[i]);
      }
      else{
        if(p->koeficijenti[i] == -1)
          printf("- ");
        else
          printf("%g ",p->koeficijenti[i]);       
      }
      
      if( i>1)
        printf("x^%d ",i);
      else
        printf("x ");
    }
    
    
  }
  
  printf("\n");
}


Polinom saberi(const Polinom* p, const Polinom *q){
  Polinom r;
  int i;
  r.stepen = (p->stepen > q->stepen ? p->stepen : q->stepen);
  
  for(i=0; i <= r.stepen; i++)
    r.koeficijenti[i] = 
    (i > p->stepen ? 0 : p->koeficijenti[i])
    +
    (i > q->stepen ? 0 : q->koeficijenti[i]);
  
  while(r.koeficijenti[r.stepen] == 0 && r.stepen != 0)
    r.stepen--;
    
    
  return r;  
}


Polinom oduzmi(const Polinom* p, const Polinom *q){
  Polinom r;
  int i;
  r.stepen = (p->stepen > q->stepen ? p->stepen : q->stepen);
  
  for(i=0; i <= r.stepen; i++)
    r.koeficijenti[i] = 
    (i > p->stepen ? 0 : p->koeficijenti[i])
    -
    (i > q->stepen ? 0 : q->koeficijenti[i]);
  
   while(r.koeficijenti[r.stepen] == 0 && r.stepen != 0)
    r.stepen--;
   
  return r;  
}


Polinom pomnozi(const Polinom* p, const Polinom *q) {
  Polinom r;
  int i,j;
  r.stepen = p->stepen + q->stepen;
  
  for(i=0; i<r.stepen ; i++)
    r.koeficijenti[i] = 0;
  
  for(i=0; i<=p->stepen; i++)
    for(j=0; j <=q->stepen; j++)
      r.koeficijenti[i+j] += 
        p->koeficijenti[i] * q->koeficijenti[j];
        
  while(r.koeficijenti[r.stepen] == 0 && r.stepen != 0)
    r.stepen--;
  
  return r;
}

Polinom uminus(const Polinom* p) {
  Polinom r = *p;
  
  int i;
  for(i=0; i<r.stepen ; i++)
    r.koeficijenti[i] *= -1;
  
  return r;
}

int jednaki(const Polinom *p, const Polinom *q) {
  if (p->stepen != q->stepen)
    return 0;
  int i;
  for (i = 0; i <= p->stepen; i++)
    if (p->koeficijenti[i] != q->koeficijenti[i])
      return 0;
  return 1;
}


float vrednost(const Polinom * p, float x)
{
    float rezultat = 0;
    int i = p->stepen;
    for (; i >= 0; i--)
		rezultat = rezultat * x + p->koeficijenti[i];
    return rezultat;
}


Polinom izvod(const Polinom * p)
{
    int i;
    Polinom r;

    if (p->stepen > 0) {
	r.stepen = p->stepen - 1;

	for (i = 0; i <= r.stepen; i++)
	    r.koeficijenti[i] = (i + 1) * p->koeficijenti[i + 1];
    } else
	r.koeficijenti[0] = r.stepen = 0;

    return r;
}

Polinom integral(const Polinom * p, float x)
{
    int i;
    Polinom r;

    r.stepen = p->stepen + 1;
    
    for (i = 1; i <= r.stepen; i++)
      r.koeficijenti[i] = 1.0 / i * p->koeficijenti[i - 1];
    r.koeficijenti[0] = x;
    
    return r;
}
