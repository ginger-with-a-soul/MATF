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
  // Vektor koji nam cuva roditelje cvorova
  std::vector<int> parents;
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
  // Alociramo mesto za V int vrednosti koje ce cuvati roditelje cvorova i sve vrednosti stavljamo na -1 jer na pocetku nijedan cvor nema roditelja
  g.parents.resize(V, -1);
}

// Dodajemo granu u -> v i v -> u, posto je graf neusmeren, mozemo to ovako da oznacimo
void add_edge(Graph &g, int u, int v)
{
  // Sused cvora v je cvor u
  g.adjacency_list[v].push_back(u);
  // Sused cvora u je cvor v
  g.adjacency_list[u].push_back(v);
}

bool BFS(Graph &g, int u)
{
  // Red koji koristimo za cuvanje cvorova grafa
  std::queue<int> nodes;

  // Dodajemo pocetni cvor iz koga krecemo
  nodes.push(u);

  // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
  int pom;

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

    // Uzimamo iteratore na pocetak i kraj vektora koji cuva susede trenutnog cvora
    auto begin = g.adjacency_list[pom].begin();
    auto end = g.adjacency_list[pom].end();

    while (begin != end) {
      // Ukoliko cvor nije posecen zelimo da ga posetimo (dodajemo ga u red) i kazemo da je trenutni cvor njegov roditelj
      if (!g.visited[*begin]) {
        g.visited[*begin] = true;
        g.parents[*begin] = pom;
        nodes.push(*begin);
      }
      // Inace ako je vec posecen i ako mu je roditelj razlicit od cvora koji se razmatra onda znaci da imamo ciklus i samo vracamo true
      else if (g.parents[pom] != *begin)
        return true;

      // Krecemo se kroz kolekciju
      begin++;
    }
  }

  // Ukoliko u petlji nismo detektovali ciklus vracamo false jer ga nema
  return false;
}

int main ()
{
  Graph g;

  initialize_graph(g, 4);

  add_edge(g, 0, 1);
  add_edge(g, 0, 2);
  add_edge(g, 1, 2);
  add_edge(g, 2, 0);
  add_edge(g, 2, 3);
  add_edge(g, 3, 3);

  // Graph g;
  // initialize_graph(g, 3);
  // add_edge(g, 0, 1);
  // add_edge(g, 1, 2);

  std::cout << BFS(g, 0) << std::endl;

  return 0;
}
