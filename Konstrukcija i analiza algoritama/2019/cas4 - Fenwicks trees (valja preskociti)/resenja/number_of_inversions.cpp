#include <iostream>
#include <vector>
#include <algorithm>

// Funkcija pomocu koje dodajemo element u stablo. Dodajemo element na odgovaraucem indeksu, i uvecavamo vrednosti svih cvorova na koje on utice
void add_to_tree(std::vector<int> &fenwick_tree, int n, int index, int value)
{
  // Uvecavam indeks za 1 jer nam u stablu indeksiranje krece od 1, a u pocetnom nizu od 0
  index++;

  // Krecemo se dok ne dodjemo do poslednjeg cvora stabla, tj kraja niza
  while (index <= n) {
    // Odgovarajuci cvor uvecavamo
    fenwick_tree[index] += value;

    // Pomeramo indeks na sledecu vrednost indeksa na koju utice promena prethodne vrednosti
    index += index & -index;
  }
}

// Ova funkcija racuna sumu svih vrednosti [0, index - 1)
int sum_to_index(std::vector<int> &fenwick_tree, int index)
{
  int sum = 0;

  // Krecemo se uz stablo tj kroz nizs
  while (index > 0) {
    // Dodajemo na sumu odgovarajuci element
    sum += fenwick_tree[index];
    // Pomeramo indeks na odgovarajuci nacin
    index -= index & -index;
  }

  return sum;
}

int main ()
{
  std::vector<int> array = { 7, -90, 100, 1 };

  int n = array.size();

  int max = *std::max_element(array.begin(), array.end());

  std::vector<int> fenwick_tree(max + 1);

  std::fill(fenwick_tree.begin(), fenwick_tree.end(), 0);

  int result = 0;

  for (int i = n - 1; i >= 0; i--) {
    result += sum_to_index(fenwick_tree, array[i]);

    add_to_tree(fenwick_tree, max, array[i] - 1, 1);
  }

  std::cout << result << std::endl;

  return 0;
}
