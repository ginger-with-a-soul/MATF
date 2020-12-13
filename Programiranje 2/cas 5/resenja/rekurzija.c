#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
Funkcija koja ispisuje cifre broja x 
sa leva na desno
*/
void ispis1(int x)
{
  if(x < 10)
  {
    printf("%d ", x);
	return;
  }
  
  ispis1(x/10);
  printf("%d ", x%10);
}

/*
Funkcija koja ispisuje cifre broja x 
sa desna na levo
*/
void ispis2(int x){
  if(x < 10)
  {
    printf("%d ", x);
	return;
  }
  
  printf("%d ", x%10);
  ispis2(x/10);
}

/*
Funkcija koja racuna broj parnih cifara
broja x
*/
int broj_parnih(int x)
{
  if(x < 10)
    return x%2 == 0 ? 1 : 0;

  if(x%2 == 0)
    return 1 + broj_parnih(x/10);
  else
    return broj_parnih(x/10);
}

/*
Funkcija koja pronalazi najvecu cifru
broja x
*/
int najveca_cifra(int x)
{
  if(x < 10)
    return x;
  
  int najveca_levo = najveca_cifra(x/10);
  
  if( x%10 > najveca_levo)
      return x%10;
  else
      return najveca_levo;
}

/*
Funkcija koja iz broja x uklanja sva pojavljivanja
cifre c
*/
int ukloni(int x, int c)
{
  if(x == 0)
    return 0;
  
  int levi_deo = ukloni(x/10, c);
  
  if(x%10 == c)
    return levi_deo;
  else
    return levi_deo*10 + x%10;
}

/*
Funkcija koja racuna duzinu broja x
*/
int duzina_broja(int broj)
{
  if(broj < 10)
    return 1;
  else
    return 1 + duzina_broja(broj/10);
}

/*
Funkcija koja cifre datog broja smesta u niz.
Prvi argument funkcije je pokazivac na kraj 
niza (niz + duzina_broja - 1)
Drugi argument funkcije je ulazni broj.
Niz se popunjava sa desna na levo
Npr. za broj 26138
i niz: | | | | | |
                |
				kraj_niza
U prvom pozivu se na kraj upisuje 8 i pokazivac se pomera u levo:
| | | | |8|
       |
	   kraj_niza
U sledecem pozivu:
| | | |3|8|
     |
	 kraj_niza
I postupak se ponavlja dok ne dodjemo do jednocifrenog broja.
Kada dodjemo do jednocifrenog broja, smestamo tu cifru u niz 
i izlazimo iz funkcije.
*/
void napravi_niz(int* kraj_niza, int broj)
{
  if(broj < 10)
  {
	kraj_niza[0] = broj;
	return;
  }
  
  kraj_niza[0] = broj%10;
  napravi_niz(kraj_niza-1, broj/10);
  
}

/*
Funkcija koja ispisuje sve elemente niza
*/
void ispisi_niz(int* niz, int n)
{
  if(n == 0)
  {
    printf("\n");
    return;
  }
  
  printf("%d ", niz[0]);
  ispisi_niz(niz+1, n-1);
}

/*
Funkcija koja ispisuje heksadekadnu vrednost
broja x 
 npr: 2345 --> 934
 
 2356/16 = 147 (4)
 147/16 = 9(3)
 9/16 = 0 (9)
 
 Treba nam ispis svakog ostatka u obrnutom poretku 9->3->4
 */
void heksa_zapis(int x)
{
  if(x == 0)
    return;
  
  heksa_zapis(x/16);
  
  if(x%16 < 10)
    printf("%d", x%16);
  else
    printf("%c", 'A' + x%16 - 10);
}

/*
Funkcija koja obrce cifre broja x
*/
int obrni(int x, int p)
{
  if(x == 0)
    return 0;
  
  return (x%10)*pow(10, p) + obrni(x/10, p-1);
}

/*
Funkcija koja obrce elemente niza a duzine n
*/
void obrni_niz(int* a, int n)
{
  if(n<=1)
    return;
  
  int tmp = *a;
  *a = a[n-1];
  a[n-1] = tmp;
  
  obrni_niz(a+1, n-2);
}

/*
Funkcija koja proverava da li su 
elementi niza uredjeni palindromski
*/
int palindrom(int* a, int n)
{
  if(n <= 1)
    return 1;
  
  if(*a != a[n-1])
    return 0;
  
  return palindrom(a+1, n-1);
}

/*
Funkcija koja dodaje 0 nakon svake 
neparne cifre broja x
*/
int dodaj_0(int x)
{
  if(x == 0)
    return 0;
  
  int levi_deo = dodaj_0(x/10);
  if(x%2)
    return levi_deo*100 + (x%10)*10;
  else
    return levi_deo*10 + x%10;
}

/*
Funkcija koja racuna skalarni proizvod nizova a i b
*/
int skalarni_proizvod(int* a, int* b, int n)
{
  if(n == 0)
    return 0;
	
  return a[0] * b[0] + skalarni_proizvod(a+1, b+1, n-1);
}

/*
Funkcija koja isrctava trougao dimenzije n.
Promenljiva "linija" sluzi da da informaciju
o tome koja linija se trenutno iscrtava
Funkcija se inicijalno poziva sa:
trougao(dimenzija,1)
*/
void trougao(int n, int linija)
{
  if(linija > n)
    return;
  
  int i;
  for(i=0; i<n-linija; i++)
    printf(" ");
  
  for(i=0; i<linija; i++)
    printf("*");
  
  printf("\n");
  
  trougao(n, linija+1);
}

/*
Funkcija koja izbacuje svaku neparnu cifru 
ako se ispred nje nalazi 2.
*/
int f3_1(int x)
{
  if(x == 0)
    return 0;
  
  int levi_deo = f3_1(x/10);
  if((x/10)%10 == 2 && x%2 == 1)
    return levi_deo;
  else
    return levi_deo*10 + x%10;
}

/*
Funkcija koja sve susedne elemente niza 
ciji je zbir x postavlja na 0.
Posto elementi koje postamtarmo u ternutnom rekurzivnom
pozivu, ucestvuju u nekom izracunavanju u narednom 
rekurzivnom pozivu, ne smemo cim naidjemo na 
par koji zadovoljava uslov da ga postavimo na 0. 
Potrebno je da sacuvamo vrednosti tog para, 
zatim da rekurzivno obidjemo ostatak niza,
a po povratku da proverimo uslov i da azuriramo
vrednosti ako je uslov ispunjen.
*/
void f1(int* a, int n, int x)
{
  if(n <= 1)
    return;
  
  int a0, a1;
  a0 = a[0];
  a1 = a[1];
  
  f1(a+1, n-1, x);
  
  if(a0 + a1 == x)
  {
    a[0] = 0;
    a[1] = 0;
  }
}

/***********************DOMACI ZADACI***********************/

/*
Funkcija koja vraca broj koji se dobija
izbacivanjem svih parnih cifara broja x
*/
int izbaci_parne(int x)
{
  if(x == 0)
    return 0;
  
  int levi_deo = izbaci_parne(x/10);
  if(x%2 == 0)
    return levi_deo;
  else
    return levi_deo*10 + x%10;
}

/*
Funkcija koja racuna najveci element niza a
*/
int maksimum_niza(int* a, int n)
{
    if(n == 1)
      return *a;
    
    int m = maksimum_niza(a+1, n-1);
    if(*a > m) // isto sto i: if(a[0] > m)
      return *a; //              return a[0]
    else
      return m;
}


/*
Funkcija koja smanjuje za 1 sve parne elemente niza 
za kojima se nalazi paran element
*/
void f3_2(int* a, int n)
{
  if(n <= 1)
    return;
  
  if(a[0] % 2 == 0 && a[1]%2 == 0)
    a[0]--;
  
  f3_2(a+1, n-1);
}


/*
Funkcija koja postavlja na 0 sve elemente koji su veci od
sume prethodnih elemenata u nizu.
U promenljivoj suma_prethodnih je potrebno akumulirati sve
vrednosti niza kroz koje smo vec prosli
Inicijalni poziv moze da bude
f3_3(niz, duzina_niza, 0);
Nakon svakog sledeceg poziva, treci argument treba da se uvecava
za vrednost tekuceg elementa niza.
*/
void f3_3(int*a, int n, int suma_prethodnih)
{
  if(n==0)
    return;
  
  int nova_suma = suma_prethodnih + *a;
  if(*a > suma_prethodnih)
    *a = 0;
  
  f3_3(a+1, n-1, nova_suma);
}

/*
Funkcija koja sve elemente koji su jednaki zbiru svojih suseda 
postavlja na 0 
*/
void f2(int* a, int n)
{
  if(n <= 2)
    return;
  
  int a0, a1, a2;
  a0 = a[0];
  a1 = a[1];
  a2 = a[2];
  
  f2(a+1, n-1);
  
  if(a0 + a2 == a1)
    a[1] = 0;
}

int main(){

  int x;
  scanf("%d", &x);

  int abs_x = abs(x);
  
  ispis1(x);
  printf("\n");
  
  ispis2(x);
  printf("\n");
  
  heksa_zapis(x);
  printf("\n");
  
  printf("Broj parnih cifara: %d\n", broj_parnih(abs_x));
 
  printf("Najveca cifra: %d\n", najveca_cifra(abs_x));
  
  printf("Uklanjamo %d: %d\n", 2, x > 0 ? ukloni(abs_x, 2) : -ukloni(abs_x, 2));
 
  int* niz = NULL;
  int duzina = duzina_broja(abs_x);
  niz = malloc(duzina * sizeof(int));
  napravi_niz(niz + duzina-1, abs_x);
  ispisi_niz(niz, duzina);
 
  printf("Broj obrnuto: %d\n", x > 0 ? obrni(abs_x, duzina-1) : -obrni(abs_x, duzina-1));
 
  obrni_niz(niz, duzina);
  ispisi_niz(niz, duzina);
 
  printf("Palindrom: %s\n", palindrom(niz, duzina) ? "DA" : "NE");
 
  printf("Izbacene parne cifre: %d\n", izbaci_parne(x));
  
  printf("Dodaj 0: %d\n", dodaj_0(abs_x));
  
  printf("Maksimum niza: %d\n", maksimum_niza(niz,duzina));
 
  printf("Skalarni proizvod: %d\n", skalarni_proizvod(niz, niz, duzina));
  
  trougao(10,1);
  
  printf("Izbacivanje svake neparne ako je 2 ispred:1322235456--> %d\n", f3_1(1322235456)); 
 
  f3_2(niz, duzina);
  ispisi_niz(niz, duzina);
 
  f3_3(niz, duzina, 0);
  ispisi_niz(niz, duzina);
 
  int tmp_niz[] = {1, 2, 7, 6, 0, 3, 2, 1, 4};
  
  f1(tmp_niz, 9, 3);
  ispisi_niz(tmp_niz, 9);
 
  int tmp_niz2[] = {1,2, 1, 1, 3, 2};
  f2(tmp_niz2, 6);
  ispisi_niz(tmp_niz2, 6);
  
  free(niz);
  return 0;
}
