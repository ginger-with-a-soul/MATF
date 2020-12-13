#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>

#define INFINITY INT_MAX

// Struktura koja predefinise operator () kako bismo u priority_queue-u kao treci argument mogli da prosledimo ovu strukturu
struct compare
{
  // Vracamo informaciju o tome da li je duzina puta para p1 veca od duzine puta para p2
  bool operator()(std::pair<int, int> &p1, std::pair<int, int> &p2)
  {
    return p1.first > p2.first;
  }
};

// Struktura kojom se predstavlja graf
struct Graph
{
  // Lista susedstva. Imamo vector parova gde je prvi element cvor ka kome void grana a drugi element tezina grane
  std::vector<std::vector<std::pair<int, int>>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Vektor koji ce da cuva tezinu puta od pocetnog cvora do svakog odgovarajuceg cvora
  std::vector<int> distances;
  // Vektor koji ce nam govoriti do kog cvora smo vec nasli najkraci put
  std::vector<bool> path_found;
};

// Funkcija koja sluzi da inicijalizuje strukturu graf (konstruktor)
// Da bismo menjali graf moramo po referenci da saljemo strukturu
// Funkcija kao argument ima samo broj cvorova grafa
void initialize_graph (Graph &g, int V)
{
  g.V = V;
  // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
  g.adjacency_list.resize(V);
  // Alociramo prostor za V integer-a, i svaki stavljamo na INFINITY. Svi cvorovi su na pocetku "beskonacno" udaljeni 
  g.distances.resize(V, INFINITY);  
  // Alociramo prostor za V bool vrednosti. Na pocetku kazemo da ni do jednog cvora nemamo put
  g.path_found.resize(V, false);
}

// Funkcija koja resetuje graf po potrebi, tj vraca sve udaljenosti i najkrace putanje na beskonacno i kaze da ni za jedan cvor nije poznata najkraca putanja
// U sustini radi slicnu stvar kao i funkcija initialize_graph (koja treba da predstavlja konstruktor za graf)
void reset_graph(Graph &g)
{
  std::fill(g.distances.begin(), g.distances.end(), INFINITY);
  std::fill(g.path_found.begin(), g.path_found.end(), false);
}

// Funkcija koja dodaje grane u -> v  i v -> u u graf
void add_edge(Graph &g, int u, int v, int weight)
{ 
  // Funkcija std::make_pair kreira par vrednosti koje se prosledjuju kao argumenti
  // Sused cvora u je cvor v, a tezina je weight
  g.adjacency_list[u].push_back(std::make_pair(v, weight));
  // Sused cvora v je cvor u a tezina je weight
  g.adjacency_list[v].push_back(std::make_pair(u, weight));
}

int dijkstra(Graph &g, int u, int v, int avoid)
{
  // Pravimo min-heap za cuvanje svih cvorova grafa. Svaki cvor heap-a ce biti cvor kao i najkrace rastojanje do njega koje je do tad nadjeno
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> heap;

  // Udaljenost pocetnog cvora od sebe samog je 0
  g.distances[u] = 0;

  // Dodajemo cvor u na heap
  heap.push(std::make_pair(g.distances[u], u));

  std::pair<int, int> tmp;

  // Dok god ima elemenata u heap-u
  while (!heap.empty()) {
    // Uzimamo koreni element heap-a
    tmp = heap.top();

    // Skidamo element sa vrha heap-a
    heap.pop();

    if (g.path_found[tmp.second])
      continue;

    // Kada udjemo u cvor znamo da smo nasli najkraci put do njega pa to i kazemo
    g.path_found[tmp.second] = true;

    // Prolazimo kroz listu suseda cvora tmp
    // tmp je par ciji je prvi element cvor a drugi cena najkraceg puta do tog cvora, tako da svuda gde nam treba cvor imamo tmp.first
    for (std::pair<int, int> &neighbour : g.adjacency_list[tmp.second]) {
      // Ako je sused trenutnog cvora bas onaj koji zelimo da izbegnemo nikada necemo azurirati putanju do njega, ona ce ostati beskonacno,
      // sto znaci da najkraci put do cvora ne moze da ide preko cvora avoid
      if (neighbour.first == avoid)
        continue;

      // Ako preko cvora tmp imamo kraci put do nekog suseda onda azuriramo najkraci put do tog suseda i dodajemo ga na heap
      // Druga opcija je da imamo put jednake tezine koji sadrzi manje grana
      if (g.distances[neighbour.first] > g.distances[tmp.second] + neighbour.second) {
        // Azuriramo tezinu puta do cvora neighbour
        g.distances[neighbour.first] = g.distances[tmp.second] + neighbour.second;
        // Dodajemo cvor neighbour zajedno sa novom tezinom puta u heap
        heap.push(std::make_pair(g.distances[neighbour.first], neighbour.first));
      }
    }
  }

  return g.distances[v];
}
  
int shortest_path_via_node(Graph &g, int u, int v, int middle)
{
  int result = dijkstra(g, u, middle, -1);
  reset_graph(g);
  return result + dijkstra(g, middle, v, -1);
}

int shortest_path_avoid(Graph &g, int u, int v, int avoid) 
{
  return dijkstra(g, u, v, avoid);
}

int main ()
{
  Graph g;

  initialize_graph(g, 5);

  add_edge(g, 0, 1, 10);
  add_edge(g, 0, 2, 2);
  add_edge(g, 1, 3, 9);
  add_edge(g, 2, 3, 7);
  add_edge(g, 2, 4, 5);
  add_edge(g, 3, 4, 6);

  // std::cout << shortest_path_via_node(g, 0, 1, 4) << std::endl;

  std::cout << shortest_path_avoid(g, 0, 3, 2) << std::endl;

  return 0;
}
