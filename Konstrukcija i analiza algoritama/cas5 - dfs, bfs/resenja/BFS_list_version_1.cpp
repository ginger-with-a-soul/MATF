#include <iostream>
#include <vector>
#include <queue>

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
}

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
}

// Obilazak grafa u sirinu
void BFS(Graph &g, int u)
{
  // Red koji koristimo za cuvanje cvorova grafa
  std::queue<int> nodes;

  // Dodajemo pocetni cvor iz koga krecemo
  nodes.push(u);

  // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
  int pom;

  // Kazemo da je pocetni cvor posecen
  g.visited[u] = true;

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

    // Uzimamo iteratore na pocetak i kraj vektora koji cuva susede trenutnog cvora
    auto begin = g.adjacency_list[pom].begin();
    auto end = g.adjacency_list[pom].end();

    while (begin != end) {
      // Ukoliko nismo vec posetili cvor zelimo i njega da posetimo, pa ga dodajemo u red kako bi u nekoj od narednih iteracija bio obradjen
      if (!g.visited[*begin]) {
        g.visited[*begin] = true;
        nodes.push(*begin);
      }
      // Krecemo se kroz kolekciju
      begin++;
    }
  }

  std::cout << "\n";
}

int main ()
{
  int v;

  std::cin >> v;

  Graph g;

  initialize_graph(g, 6);

  add_edge(g, 0, 1);
  add_edge(g, 0, 2);
  add_edge(g, 1, 3);
  add_edge(g, 1, 4);
  add_edge(g, 2, 3);
  add_edge(g, 4, 5);

  BFS(g, v);

  return 0;
}
