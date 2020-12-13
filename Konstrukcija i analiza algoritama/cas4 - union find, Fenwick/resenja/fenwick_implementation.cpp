#include <iostream>
#include <vector>

int recursive_sum(std::vector<int> &fenwick_tree, int index)
{
  if (index == 0) return 0;

  return recursive_sum(fenwick_tree, index - (index & (- index))) + fenwick_tree[index];
}

// Funkcija koja racuna sumu elemenata do odredjenog indeksa u Fenwick-ovom stablu
int sum_to_index(std::vector<int> &fenwick_tree, int index)
{
  // Uvecavamo indeks jer nam indeksiranje krece 1, a u pocetnom nizu indeksiranje krece od 0, tako da ako trazimo u nizu { 1, 2, 3, 4, 5 } sumu do indeksa 3 to je suma 1 + 2 + 3 + 4
  // Niz koji predstavlja Fenwick-ovo drvo je oblika { 0, 1, 2, 3, 4, 5 } i indeksom 3 pokrivamo samo 0, 1, 2, 3, zato uvecamo indeks da uzmemo brojeve 1, 2, 3, 4 i 0 koja nam nije bitna
  index++;

  // Inicijalizujemo rezultat na 0
  int result = 0;

  // Krecemo se "uz stablo" tj sdesna nalevo u nizu dok ne dodjemo do "korena" odnosno do pocetnog indeksa
  while (index > 0) {
    // Uvecavamo rezultat za odgovarajuci element stabla
    result += fenwick_tree[index];
    // Menjamo vrednost indeksa na odgovarajuci nacin kako bismo se kretali "uz stablo"
    index -= index & (-index);
  }

  // Vracamo odgovarajuci rezultat
  return result;
}

void add_recursive(std::vector<int> &fenwick_tree, int n, int index, int value)
{
  if (index > n) return ;

  fenwick_tree[index] += value;
  add_recursive(fenwick_tree, n, index + (index & (-index)), value);
}

// Funkcija pomocu koje dodajemo element u stablo. Dodajemo element na odgovaraucem indeksu, i uvecavamo vrednosti svih cvorova na koje on utice
void add_to_tree(std::vector<int> &fenwick_tree, int n, int index, int value)
{
  // Uvecavamo indeks za 1 jer nam u stablu indeksiranje krece od 1, a u pocetnom nizu od 0
  index++;

  // Krecemo se dok ne dodjemo do poslednjeg cvora stabla, tj kraja niza
  while (index <= n) {
    // Odgovarajuci cvor uvecavamo
    fenwick_tree[index] += value;
    // Pomeramo indeks na sledecu vrednost indeksa na koju utice promena prethodne vrednosti
    index += index & (-index);
  }
}

// Funkcija sum_to_index vraca sumu elemenata [0, index]. Ova funkcija je samo wrapper da mozemo od proizvoljnog do proizvoljnog indeksa da trazimo sumu, recimo [2, 3]
int sum_in_segment(std::vector<int> &fenwick_tree, int index_1, int index_2)
{
  return sum_to_index(fenwick_tree, index_2) - sum_to_index(fenwick_tree, index_1 - 1);
}

int main ()
{
  std::vector<int> array = { 2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9 };

  int n = array.size();

  std::vector<int> fenwick_tree(n + 1), fenwick_recursive(n + 1);

  /********* C++ deo *********/
  // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
  std::fill(fenwick_tree.begin(), fenwick_tree.end(), 0);

  for (int i = 0; i < n; i++) {
    add_recursive(fenwick_recursive, n, i + 1, array[i]);
    add_to_tree(fenwick_tree, n, i, array[i]);
  }

  int a = 2;
  int b = 5;

  std::cout << sum_in_segment(fenwick_tree, a, b) << std::endl;
  std::cout << recursive_sum(fenwick_recursive, b + 1) - recursive_sum(fenwick_recursive, a) << "\n";

  return 0;
}
