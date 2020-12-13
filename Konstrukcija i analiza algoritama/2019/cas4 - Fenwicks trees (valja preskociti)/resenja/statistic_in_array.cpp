#include <iostream>
#include <vector>
#define MAX 1000

// Funkcija pomocu koje dodajemo element u stablo. Dodajemo element na odgovaraucem indeksu, i uvecavamo vrednosti svih cvorova na koje on utice
void update_tree(std::vector<int> &fenwick_tree, int index, int value)
{
  // Uvecavamo indeks za 1 jer nam u stablu indeksiranje krece od 1, a u pocetnom nizu od 0
  index++;

  // Krecemo se dok ne dodjemo do poslednjeg cvora stabla, tj kraja niza
  while (index <= MAX) {
    // Odgovarajuci cvor uvecavamo
    fenwick_tree[index] += value;
    // Pomeramo indeks na sledecu vrednost indeksa na koju utice promena prethodne vrednosti
    index += index & (-index);
  }
}

// Funkcija koja racuna sumu elemenata do odredjenog indeksa u Fenwick-ovom stablu
int sum_to_index(std::vector<int> &fenwick_tree, int index)
{
  // Uvecavamo indeks jer nam indeksiranje krece 1, a u pocetnom nizu indeksiranje krece od 0, tako da ako trazimo u nizu { 1, 2, 3, 4, 5 } sumu do indeksa 3 to je suma 1 + 2 + 3 + 4
  // Niz koji predstavlja Fenwick-ovo drvo je oblika { 0, 1, 2, 3, 4, 5 } i indeksom 3 pokrivamo samo 0, 1, 2, 3, zato uvecamo indeks da uzmemo brojeve 1, 2, 3, 4 i 0 koja nam nije bitna
  index++;

  // Inicijalizujemo rezultat na 0
  int sum = 0;

  // Krecemo se "uz stablo" tj sdesna nalevo u nizu dok ne dodjemo do "korena" odnosno do pocetnog indeksa
  while (index > 0) {
    // Uvecavamo rezultat za odgovarajuci element stabla
    sum += fenwick_tree[index];
    // Menjamo vrednost indeksa na odgovarajuci nacin kako bismo se kretali "uz stablo
    index -= index & (-index);
  }

  // Vracamo odgovarajuci rezultat
  return sum;
}

// Trazimo k-ti najmanji element u nizu
// Najjednostavniji nacin da to uradimo je da radimo binarnu pretragu kroz stablo
// Posto svaki element stabla cuva broj pojavljivanja elementa iz niza mozemo da koristimo funkciju sum() do odgovarajuceg indeksa kako bismo dobili koliko je elemenata manjih od njega
// u stablu. Binarnom pretragom mozemo doci do k-tog najmanjeg elementa
int find_kth_smallest(std::vector<int> &fenwick_tree, int k)
{
  // Levi kraj
  int l = 1;
  // Desni kraj
  int r = fenwick_tree.size();
  int middle;

  while (l < r) {
    // Racunamo indeks srednjeg elementa, i onda gledamo idemo li levo ili desno
    middle = (l + r) / 2;

    // Ukoliko je k-ti element levo od sredine niza idemo levo
    if (k <= sum_to_index(l, middle)
      r = middle;
    // Inace idemo desno
    else
      l = middle + 1;
  }

  return l;
}

// Funkcija za ubacivanje elementa u stablo. Uvek cemo dodavati vrednost 1, samo kako bismo oznacili da se odredjeni element javlja u nizu, recimo ako treba da dodamo 20 stavicemo
// na poziciju 21 u Fenwick-ovom stablu 1, kao indikator da se broj 20 javlja. Ukoliko se 20 javlja vise puta svaki put uvecanjem za 1 cemo zapravo imati broj pojavljivanja broja
// 20 u stablu
void insert_into_tree(std::vector<int> &fenwick_tree, int value)
{
  update_tree(fenwick_tree, value, 1);
}

// Funkcija za izbacivanje elementa iz stabla. Uvek cemo oduzimati vrednost 1, samo kako bismo oznacili da se jedno pojavljivanje elementa izbacuje. Recimo ako treba da izbacimo
// 20 na poziciji 21 u Fenwick-ovom stablu cemo oduzeti 1. Ukoliko se 20 izbacuje vise puta svaki put smanjenjem za 1 cemo zapravo "izbacivati" broj 20 odgovarajuci broj puta
void delete_from_tree(std::vector<int> &fenwick_tree, int value)
{
  update_tree(fenwick_tree, value, -1);
}

// Funkcija za racunanje ranga elementa, tj pozicije elementa u sortiranom nizu
// Najjednostavniji nacin da to odredimo je suma elemenata od 0 do vrednost_elementa
// Recimo za broj 20 racunamo sumu [0-20], ukoliko zelimo da za najmanji element vracamo 1, inace sumu [0-19] ukoliko zelimo da za najmanji element vracamo rang 0
int rang_of_element(std::vector<int> &fenwick_tree, int value)
{
  return sum_to_index(fenwick_tree, value);
}

int main ()
{
  std::vector<int> fenwick_tree(MAX + 1);

  update_tree(fenwick_tree, 20, 1);
  update_tree(fenwick_tree, 50, 1);
  update_tree(fenwick_tree, 30, 1);
  update_tree(fenwick_tree, 40, 1);

  // for (int i = 0; i < fenwick_tree.size(); i++)
  //   std::cout << fenwick_tree[i] << " ";

  std::cout << rang_of_element(fenwick_tree, 50) << "\n";

  return 0;
}
