#include <iostream>
#include <vector>
#include <algorithm>

// Struktura koja ce predstavljati cvor stabla, odnosno element niza
struct Node
{
  // Promenljiva koja cuva poziciju upita, ukoliko cvor predstavlja element niza a ne upit vrednost je 0
  int position;
  // Levi deo segmenta. Ukoliko cvor ne predstavlja upit nego element niza vrednost je 0
  int left;
  // Desni deo segmenta. Ukoliko je cvor element niza a ne upit ova promenljiva predstavlja poziciju elementa u nizu
  int right;
  // Cuva vrednost k u odnosu na koju trazimo vece elemente ukoliko je u pitanju upit, inace vrednost elementa niza
  int value;
};

// Funkcija koju prosledjujemo funkciji sort, pomocu koje odredjujemo na koji nacin zelimo da elementi budu sortirani
bool compare (Node &node_1, Node &node_2)
{
  // Ukoliko imamo upit i element niza koji imaju istu vrednost, tj k iz upita je jednako vrednosti elementa niza, prvo stavljamo upit pa onda element niza
  if (node_1.value == node_2.value)
    return node_1.left > node_2.left;

  // Inace, sortiramo elemente niza u opadajucem poretku
  return node_1.value > node_2.value;
}

// Funkcija za azuriranje Fenwick-ovog stabla. Ideja je da za svaki broj koji se javlja brojimo broj pojavljivanja, zato uvecavamo vrednost na poziciji za 1
void update_tree (std::vector<int> &fenwick_tree, int n, int index)
{
  // Krecemo se kroz stablo, tj ka kraju niza
  while (index <= n) {
    // Uvecavamo vrednost na odgovarajucoj poziciji
    fenwick_tree[index]++;
    // Pomeramo indeks na odgovarajucu poziciju
    index += index & (-index);
  }
}

// Funkcija koja broji broj elemenata koji postoje do indeksa index
int query (std::vector<int> &fenwick_tree, int index)
{
  // Broj elemenata na pocetku je 0
  int count = 0;

  // Krecemo se uz stablo, tj ka pocetku niza
  while (index > 0) {
    // Uvecavamo broj elemenata
    count += fenwick_tree[index];
    // Pomeramo indeks na odgovarajucu poziciju
    index -= index & (-index);
  }

  // Vracamo broj elemenata do indeksa index
  return count;
}

// Funkcija u kojoj pravimo stablo, i koja resava upite
void solve_queries(std::vector<int> &array, std::vector<int> &left_ends, std::vector<int> &right_ends, std::vector<int> &k_values)
{
  // Broj elemenata niza
  int n = array.size();
  // Ukupan broj upita
  int num_of_queires = left_ends.size();

  // Vektor u koji smestamo i upite i elemente pocetnog niza, indeksiranje krece od 1, pa imamo jos + 1
  Node nodes[n + num_of_queires + 1];

  // Dodajemo elemente niza
  for (int i = 1; i <= n; i++) {
    // Vrednost je vrednost odgovarajuceg elementa niza
    nodes[i].value = array[i - 1];
    // Pozicija za elemente niza je 0
    nodes[i].position = 0;
    // Levi kraj za elemente niza je 0
    nodes[i].left = 0;
    // Desni kraj za elemente niza je bas pozicija u nizu
    nodes[i].right = i;
  }

  // Dodajemo upite
  for (int i = n + 1; i <= n + num_of_queires; i++) {
    // Pozicija upita je i - n
    nodes[i].position =  i - n;
    // Vrednost je k odgovarajuceg upita
    nodes[i].value = k_values[i - n - 1];
    // Levi kraj za upit je levi kraj odgovarajuceg levog kraja iz niza upita
    nodes[i].left = left_ends[i - n - 1];
    // Desni kraj za upit je desni kraj odgovarajuceg desnog kraja iz niza upita
    nodes[i].right = right_ends[i - n - 1];
  }

  // Sortiramo niz u opadajucem poretku koristeci funkciju compare
  /********* C++ deo *********/
  // Funkcija std::sort sortira kolekciju elemenata, a kao argumente dobija pocetak, kraj kolekcije i eventualno funkciju bool compare(<T> el1, <T> el2) gde <T> predstavlja bilo koji tip
  // Ukoliko je prosledjena funkcija ona se koristi za sortiranje inace je sortiranje po default-u u rastucem poretku. U nasem slucaju je funkcija oblika
  // bool compare (Node &node_1, Node &node_2)
  std::sort(nodes + 1, nodes + n + num_of_queires + 1, compare);

  // Formiramo Fenwick-ovo drvo velicine n
  std::vector<int> fenwick_tree(n + 1);

  // Popunjavamo niz nulama
  /********* C++ deo *********/
  // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
  std::fill(fenwick_tree.begin(), fenwick_tree.end(), 0);

  // Niz u kome cuvamo odgovore, tj broj elemenata koji su veci od k za svaki od upita
  std::vector<int> answer_array(num_of_queires + 1);

  for (int i = 1; i <= n + num_of_queires; ++i) {
    std::cout << nodes[i].position << " " << nodes[i].left << " " << nodes[i].right << " " << nodes[i].value << std::endl;
  }

  int count;

  for (int i = 1; i <= n + num_of_queires; i++) {
    // Ukoliko je clan niza koji razmatramo upit onda brojimo koliko ima elemenata u intervalu [left, right] koji su veci od k
    if (nodes[i].position != 0) {
      count = query(fenwick_tree, nodes[i].right) - query(fenwick_tree, nodes[i].left - 1);

      // Pozicija upita u nizu upita nam govori gde treba u niz sa odgovorima da stavimo odgovarajuci broj elemenata
      answer_array[nodes[i].position] = count;
    }
    // Inace azuriramo stablo
    else {
      update_tree(fenwick_tree, n, nodes[i].right);
    }
  }

  // Ispisujemo odgovore
  for (int i = 1; i <= num_of_queires; i++)
    std::cout << answer_array[i] << std::endl;
}

int main ()
{
  std::vector<int> array = { 7, 3, 9, 13, 5, 4 };


  // Levi krajevi intervala u kojima vrsimo upite
  std::vector<int> left_ends = { 1, 2 };
  // Desni krajevi intervala u kojima vrsimo upite
  std::vector<int> right_ends = { 4, 6 };
  // Vrednosti k za koje trazimo elemente koji su veci
  std::vector<int> k_values = { 6, 8 };

  solve_queries(array, left_ends, right_ends, k_values);

  return 0;
}
