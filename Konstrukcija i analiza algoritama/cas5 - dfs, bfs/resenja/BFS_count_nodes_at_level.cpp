#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// Struktura kojom se predstavlja graf
struct Graph
{
	// Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Lista nivoa za svaki od cvorova
  std::vector<int> levels;
};

// Funkcija koja sluzi da inicijalizuje strukturu graf (konstruktor)
// Da bismo menjali graf moramo po referenci da saljemo strukturu
// Funkcija kao argument ima samo broj cvorova grafa
void initialize_graph (Graph &g, int V)
{
	g.V = V;
	// Alociramo mesto za V bool vrednosti koje ce cuvati posecene cvorove, i sve odmah stavljamo na false, jer na pocetku nijedan cvor nije posecen
  g.visited.resize(V, false);
  // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
  g.adjacency_list.resize(V);
  // Alociramo mesto za V int vrednosti koje ce cuvati nivoe cvorova
  g.levels.resize(V);
}

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
}

// Obilazak grafa u sirinu
void BFS(Graph &g, int u, int level)
{
  // Red koji koristimo za cuvanje cvorova grafa
  std::queue<int> nodes;

  // Dodajemo pocetni cvor iz koga krecemo
  nodes.push(u);

  g.visited[u] = true;

  // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
  int pom;

  // Nivo korenog cvora je 0
  int current_level = 0;

  g.levels[u] = current_level;

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

    // Uzimamo iteratore na pocetak i kraj vektora koji cuva susede trenutnog cvora
    auto begin = g.adjacency_list[pom].begin();
    auto end = g.adjacency_list[pom].end();

    while (begin != end) {
      // Ukoliko nismo vec posetili cvor zelimo i njega da posetimo, pa ga dodajemo u red kako bi u nekoj od narednih iteracija bio obradjen
      if (!g.visited[*begin]) {
        g.visited[*begin] = true;
        // Cvor svakog od potomaka je za jedan veci od nivoa oca
        g.levels[*begin] = g.levels[pom] + 1;
        nodes.push(*begin);
      }

      // Krecemo se kroz kolekciju
      begin++;
    }
  }

  // Brojac cvorova na nivou level
  int counter = 0;

  // Prolazimo kroz listu nivoa i
  for (int x : g.levels) {
    // Ako je cvor na nivou level uvecavamo brojac
    if (x == level)
      counter++;
  }

  std::cout << std::count_if(g.levels.begin(), g.levels.end(), [&level](int x){ return x == level; }) << std::endl;
}

int main ()
{
  Graph g;

  initialize_graph(g, 8);

  add_edge(g, 0, 1);
  add_edge(g, 0, 4);
  add_edge(g, 0, 7);
  add_edge(g, 4, 6);
  add_edge(g, 4, 5);
  add_edge(g, 4, 2);
  add_edge(g, 7, 3);

  int level;

  std::cin >> level;

  BFS(g, 0, level);

  return 0;
}
