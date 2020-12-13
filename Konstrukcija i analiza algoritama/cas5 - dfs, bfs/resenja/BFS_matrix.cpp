#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <algorithm>

// Klasa kojom cemo predstavljati graf
class Graph
{
public:
  // Konstruktor za graf koji samo prima broj cvorova grafa
  Graph(int V)
  {
    // Broj cvorova grafa je jednak prosledjenom argumentu
    this->V = V;
    // Alociramo mesto za V bool vrednosti koje ce cuvati posecene cvorove
    visited.resize(V);
    // Na pocetku nijedan cvor nije posecen
    /********* C++ deo *********/
    // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std:fill(visited.begin(), visited.end(), false);

    // Alociramo prostor za niz nizova, tj matricu, u C++-u moramo da imamo eksplicitno kastovanje u (int **), odsnosno (int *) inace se g++ buni
    matrix = (int **)malloc(V * sizeof(int *));
    // Svaki od elemenata matrice je novi niz, pa se alocira i memorija za njih
    for (int i = 0; i < V; i++)
      matrix[i] = (int *)calloc(sizeof(int), V);
  }

  // Destruktor za klasu graf
  /********* C++ deo *********/
  // Destruktori su slicni kao konstruktori, samo sto sluze za oslobadjanje resursa (oslobadjanje memorije, zatvaranje datoteka ako su neke bile otvorene itd.)
  // Destruktor se uvek poziva kada objekat prestaje da postoji. Ukoliko je objekat instanciran bez kljucne reci new onda se on prestaje da postoji kada se izadje iz
  // scope-a u kome je on definisa. Npr ako imamo sledece:
  // void f()
  // {
  //   Graph g(2);
  // }
  // Nakon sto se zavrsi funkcija f i graf g prestaje da postoji pa se poziva destruktor za njega. Mi smo u konstruktoru alocirali memoriju pa je u destruktoru oslobadjamo
  ~Graph()
  {
    // Oslobadjamo svaki pojedinacni element (kolonu) matrice
    for (int i = 0; i < V; i++)
      free(matrix[i]);

    // Oslobadjamo memoriju rezervisanu za niz nizova
    free(matrix);
  }

  // Funkcija koja dodaje granu u -> v u graf
  void add_edge(int u, int v)
  {
    // Koristimo matricu povezanosti pa imamo da je [u][v] == 1 ako grana postoji, a 0 inace
    matrix[u][v] = 1;
  }

  // Obilazak grafa u sirinu
  void BFS(int u)
  {
    // Red koji koristimo za cuvanje cvorova grafa
    std::queue<int> nodes;

    visited[u] = true;
    
    // Dodajemo pocetni cvor iz koga krecemo
    nodes.push(u);

    // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
    int pom;

    // Idemo dok god imamo cvorova u redu
    while (!nodes.empty()) {
      // Uzimamo cvor sa pocetka reda
      /********* C++ deo *********/
      // Metod front() samo uzima element sa pocetka reda ali ga i ne uklanja
      pom = nodes.front();
      // Skidamo cvor sa pocetka reda
      /********* C++ deo *********/
      // Metod pop() skida element sa pocetka reda
      nodes.pop();

      // Ispisujemo trenutni cvor
      std::cout << pom << " ";

      // Krecemo se kroz matricu susedstva i ukoliko grana postoji izmedju 2 cvora a dodatno cvor ka kome grana vodi nije vec vidjen, posecujemo taj cvor rekurzivno
      for (int i = 0; i < V; i++) {
        // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove, dodatno mora da postoji grana od pom do tog cvora.
        if (!visited[i] && matrix[pom][i]) {
            visited[i] = true;          
            nodes.push(i);
        }
      }
    }

    std::cout << "\n";
  }

private:
  // Broj cvorova grafa
  int V;
  // Matrica susedstva
  int **matrix;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
};

int main ()
{
  int v;

  std::cin >> v;

  Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 0);
  g.add_edge(2, 3);
  g.add_edge(3, 3);

  g.BFS(v);

  return 0;
}
