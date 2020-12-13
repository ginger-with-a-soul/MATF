#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <stack>

#define INFINITY INT_MAX

// Struktura celija koja cuva poziciju celije kao i njenu udaljenost od celije (0, 0)
class cell
{
public:

  // Konstruktor bez argumenata
  cell()
  {

  }

  // Konstruktor za celiju koji dobija poziciju celije i udaljenost od pocetka
  cell(int i, int j, int distance)
  {
    this->i = i;
    this->j = j;
    this->distance = distance;
  }

  int i;
  int j;
  int distance;
};

// Struktura koja predefinise operator () kako bismo u priority_queue-u kao treci argument mogli da prosledimo ovu strukturu
struct compare
{
  bool operator()(const cell &c_1, const cell &c_2)
  {
    // Vracamo informaciju o tome da li je duzina puta do c_1 manja od duzine puta do c_2
    return c_1.distance < c_2.distance;
  }
};

// Struktura kojom se predstavlja graf
struct Graph
{
  // Broj cvorova grafa
  int V;
  // Umesto vektora distances cuvacemo matricu jer ce nam i lavirint biti dat kao matrica, pa cemo lako azurirati vrednost distances za svaki od cvorova
  int **distances;
};

// Funkcija koja sluzi da inicijalizuje strukturu graf (konstruktor)
// Da bismo menjali graf moramo po referenci da saljemo strukturu
// Funkcija kao argument ima samo broj cvorova grafa
void initialize_graph (Graph &g, int V)
{
  // Broj cvorova grafa je jednak prosledjenom argumentu
  g.V = V;
  // Alociramo prostor za niz nizova, tj matricu, u C++-u moramo da imamo eksplicitno kastovanje u (int **), odsnosno (int *) inace se g++ buni
  g.distances = (int **)malloc(V * sizeof(int *));
  // Svaki od elemenata matrice je novi niz, pa se alocira i memorija za njih
  for (int i = 0; i < V; i++)
    g.distances[i] = (int *)malloc(V * sizeof(int));

  // Kazemo da je svaki element matrice distances jednak INFINITY
  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      g.distances[i][j] = INFINITY;
}
    
void dijkstra(Graph &g, int maze[][5], int n)
{
  // Umesto min-heap-a cemo koristiti std::set jer i on ima uredjenost, i mozemo uvek uzimati set.begin() koji ce biti prvi najmanji element
  std::set<cell, compare> set;

  // Pravimo celiju koja odgovara celiji (0, 0) i postavljamo njene koordinate na (0, 0) i udaljenost od nje same na vrednost lavirinta na koordinatama (0, 0)
  cell tmp;
  tmp.i = 0;
  tmp.j = 0;
  tmp.distance = maze[0][0];

  // Dodajemo cvor (0, 0) u skup
  set.insert(tmp);

  // Udaljenost pocetnog cvora od sebe samog je ono sto je u lavirintu na poziciji 0, 0
  g.distances[0][0] = tmp.distance;

  // Dok god ima elemenata u skupu
  while (!set.empty()) {
    // Uzimamo prvi element skupa
    tmp = *set.begin();

    // Brisemo prvi element skupa, jer jednom kad uzmemo cvor nasli smo najkraci put do njega
    set.erase(set.begin());

    // Element iznad
    // Ukoliko je put do ove celije preko celije tmp kraci nego neki koji je pre postojao azuriramo vrednost puta
    if (tmp.i - 1 >= 0 && g.distances[tmp.i - 1][tmp.j] > g.distances[tmp.i][tmp.j] + maze[tmp.i - 1][tmp.j]) {

      // Ukoliko smo vec azurirali vrednost za celiju znaci da smo je ubacili u skup pa hocemo da obrisemo trenutno pojavljivanje i zamenimo ga novim
      if (g.distances[tmp.i - 1][tmp.j] != INFINITY)
        /************* C++ deo *************/
        // Metod erase() dobija pokazivac (iterator) na element koji treba obrisati, a metod find() vraca iterator na element koji je pronadjen
        set.erase(set.find(cell(tmp.i - 1, tmp.j, g.distances[tmp.i - 1][tmp.j])));

      // Azuriramo udaljenost do celije iznad trenutne i ubacimo novo (azurirano) pojavljivanje u skup
      g.distances[tmp.i - 1][tmp.j] = g.distances[tmp.i][tmp.j] + maze[tmp.i - 1][tmp.j];
      set.insert(cell(tmp.i - 1, tmp.j, g.distances[tmp.i - 1][tmp.j]));
    }

    // Element ispod
    // Ukoliko je put do ove celije preko celije tmp kraci nego neki koji je pre postojao azuriramo vrednost puta
    if (tmp.i + 1 < n && g.distances[tmp.i + 1][tmp.j] > g.distances[tmp.i][tmp.j] + maze[tmp.i + 1][tmp.j]) {

      // Ukoliko smo vec azurirali vrednost za celiju znaci da smo je ubacili u skup pa hocemo da obrisemo trenutno pojavljivanje i zamenimo ga novim
      if (g.distances[tmp.i + 1][tmp.j] != INFINITY)
        /************* C++ deo *************/
        // Metod erase() dobija pokazivac (iterator) na element koji treba obrisati, a metof find() vraca iterator na element koji je pronadjen
        set.erase(set.find(cell(tmp.i + 1, tmp.j, g.distances[tmp.i + 1][tmp.j])));

      // Azuriramo udaljenost do celije ispod trenutne i ubacimo novo (azurirano) pojavljivanje u skup
      g.distances[tmp.i + 1][tmp.j] = g.distances[tmp.i][tmp.j] + maze[tmp.i + 1][tmp.j];
      set.insert(cell(tmp.i + 1, tmp.j, g.distances[tmp.i + 1][tmp.j]));
    }

    // Element levo
    // Ukoliko je put do ove celije preko celije tmp kraci nego neki koji je pre postojao azuriramo vrednost puta
    if (tmp.j - 1 >= 0 && g.distances[tmp.i][tmp.j - 1] > g.distances[tmp.i][tmp.j] + maze[tmp.i][tmp.j - 1]) {

      // Ukoliko smo vec azurirali vrednost za celiju znaci da smo je ubacili u skup pa hocemo da obrisemo trenutno pojavljivanje i zamenimo ga novim
      if (g.distances[tmp.i][tmp.j - 1] != INFINITY)
        /************* C++ deo *************/
        // Metod erase() dobija pokazivac (iterator) na element koji treba obrisati, a metof find() vraca iterator na element koji je pronadjen
        set.erase(set.find(cell(tmp.i, tmp.j - 1, g.distances[tmp.i][tmp.j - 1])));

      // Azuriramo udaljenost do celije levo od trenutne i ubacimo novo (azurirano) pojavljivanje u skup
      g.distances[tmp.i][tmp.j - 1] = g.distances[tmp.i][tmp.j] + maze[tmp.i][tmp.j - 1];
      set.insert(cell(tmp.i, tmp.j - 1, g.distances[tmp.i][tmp.j - 1]));
    }

    // Element desno
    // Ukoliko je put do ove celije preko celije tmp kraci nego neki koji je pre postojao azuriramo vrednost puta
    if (tmp.j + 1 < n && g.distances[tmp.i][tmp.j + 1] > g.distances[tmp.i][tmp.j] + maze[tmp.i][tmp.j + 1]) {

      // Ukoliko smo vec azurirali vrednost za celiju znaci da smo je ubacili u skup pa hocemo da obrisemo trenutno pojavljivanje i zamenimo ga novim
      if (g.distances[tmp.i][tmp.j + 1] != INFINITY)
        /************* C++ deo *************/
        // Metod erase() dobija pokazivac (iterator) na element koji treba obrisati, a metof find() vraca iterator na element koji je pronadjen
        set.erase(set.find(cell(tmp.i, tmp.j + 1, g.distances[tmp.i][tmp.j + 1])));

      // Azuriramo udaljenost do celije levo od trenutne i ubacimo novo (azurirano) pojavljivanje u skup
      g.distances[tmp.i][tmp.j + 1] = g.distances[tmp.i][tmp.j] + maze[tmp.i][tmp.j + 1];
      set.insert(cell(tmp.i, tmp.j + 1, g.distances[tmp.i][tmp.j + 1]));
    }
  }

  std::cout << g.distances[n - 1][n - 1] << std::endl;
}

int main ()
{
  Graph g;

  initialize_graph(g, 5);

  int maze[5][5] = {
        { 31, 100, 65, 12, 18 },
        { 10, 13, 47, 157, 6 },
        { 100, 113, 174, 11, 33 },
        { 88, 124, 41, 20, 140 },
        { 99, 32, 111, 41, 20 }
  };

  dijkstra(g, maze, 5);

  return 0;
}
