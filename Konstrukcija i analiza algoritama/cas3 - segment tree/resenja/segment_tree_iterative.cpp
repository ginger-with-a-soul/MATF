#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Funkcija koja od niza array kreira segmentno stablo segment_tree
void build_segment_tree(std::vector<int> &array, std::vector<int> &segment_tree, int n)
{
  // Kopiramo sve elemente niza array (kojih ima ukupno n) u segmentno stablo od pozicije n pa do kraja
  /********* C++ deo *********/
  // std::copy_n() kao prvi argument dobija poziciju u kolekciji od koje se kopira, kao drugi broj elemenata koje je potrebno kopirati, i kao treci pocetnu poziciju
  // (od koje smestamo elemente) u kolekciji u koju kopiramo
  std::copy_n(array.begin(), n, segment_tree.begin() + n);

  // Svaki roditelj ima svoju decu na pozicijama 2 * k i 2 * k + 1 (indeksiranje krecemo od 1)
  for(int k = n - 1; k >= 1; k--)
    segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<int> segment_tree(size);

  build_segment_tree(array, segment_tree, n);

  for (int x : segment_tree)
    std::cout << x << " ";

  std::cout << "\n";

  return 0;
}
