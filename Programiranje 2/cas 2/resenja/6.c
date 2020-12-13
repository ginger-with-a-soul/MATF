#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define IME 5

typedef struct{
  unsigned int a,b;
  char ime[IME];
}PRAVOUGAONIK;

void greska()
{
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
  
  //Proveravamo da li su navedeni potrebni argumenti
  if(argc != 2)
    greska();
  
  /*NAPOMENA:
   Najispravnije je koristiti unsigned kao tip za max_pov jer su a i b tog tipa, 
   pa bi u slucaju velikih brojeva koji ne mogu stati u int doslo do greske pri racunanju
   povrsine. Ako bi ipak pretpostavili da program nece biti testiran za brojeve vece od
   MAX_INT i ako se koristi int za max_pov treba voditi racuna o sledecem:
   ako se max_pov inicijalizuje na -1,
   poredjenje if(p.a*p.b > max_pov) nece raditi ispravno
   iz razloga sto kada mesamo unsigned i signed int, 
   svi operandi se tretiraju kao da su unsigned! 
   Kako su p.a i p.b neoznaceni brojevi, a -1 oznacen,
   desava se da se u poredjenju -1 tretira kao neoznacen broj (i to jako
   veliki broj jer ima vodecu jedinicu). 
   Ovo je greska koja se u kodu jako tesko pronalazi, 
   kada se ubaci fleg -Wall, nece se ispisati nikakvo upozorenje,
   ali koriscenjem -Wextra dobijate upozorenje:
   warning: comparison between signed and unsigned integer expressions
   Probajte!
   */
  unsigned max_pov = 0;
  PRAVOUGAONIK p;
  
  //Otvaramo fajl za citanje
  FILE* ulaz = fopen(argv[1], "r");
  if(ulaz == NULL)
    greska();
  
  //Citamo iz fajla sve dok ne dodjemo do kraja
  while(fscanf(ulaz, "%u%u%s", &p.a, &p.b, p.ime) == 3){
    //Proveravamo da li su podaci ispravni
    if(p.a == 0 || p.b == 0)
      greska();
    
    //Obradjujemo trenutni pravougaonik
    if(p.a == p.b)
      printf("%s ", p.ime);
    else{
      if(p.a*p.b > max_pov)
        max_pov = p.a*p.b;
    }
  }
  
  //Ispisujemo povrsinu najveceg pravougaonika
  if(max_pov != 0)
    printf("%u\n", max_pov);
  else
    printf("\n");
 
  //Zatvaramo datoteku
  fclose(ulaz);
  return 0;
}
