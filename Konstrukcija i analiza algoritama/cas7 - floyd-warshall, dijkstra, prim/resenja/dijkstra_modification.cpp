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
  // Vektor koji za svaki cvor cuva duzinu najkraceg puta do tog cvora
  std::vector<int> shortest_path;
  // Vektor koji cuva roditelja za svaki cvor, tj cvor preko koga se dolazi do cvora u najkracoj putanji, ovo sluzi kako bismo mogli da rekonstruisemo putanju
  std::vector<int> parents;
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
  // Alociramo prostor za V integer-a. Na pocetku su putanje do svakog cvora beskonacne
  g.shortest_path.resize(V, INFINITY);
  // Alociramo prostor za V integer-a. Na pocetku su svi roditelji -1
  g.parents.resize(V, -1);
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

void dijkstra(Graph &g, int u, int v)
{
  // Pravimo min-heap za cuvanje svih cvorova grafa. Svaki cvor heap-a ce biti cvor kao i najkrace rastojanje do njega koje je do tad nadjeno
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> heap;

  // Udaljenost pocetnog cvora od sebe samog je 0
  g.distances[u] = 0;

  // Najkraci put od pocetnog cvora do samog sebe je 0
  g.shortest_path[u] = 0;

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
      // Ako preko cvora tmp imamo kraci put do nekog suseda onda azuriramo najkraci put do tog suseda i dodajemo ga na heap
      // Druga opcija je da imamo put jednake tezine koji sadrzi manje grana
      if (g.distances[neighbour.first] > g.distances[tmp.second] + neighbour.second || 
         (g.distances[neighbour.first] == g.distances[tmp.second] + neighbour.second && 
          g.shortest_path[neighbour.first] > g.shortest_path[tmp.second] + 1)) {
        // Azuriramo duzinu najkraceg put do cvora neighbour
        g.shortest_path[neighbour.first] = g.shortest_path[tmp.second] + 1;
        // Azuriramo roditeljski cvor cvora neighbour
        g.parents[neighbour.first] = tmp.second;
        // Azuriramo tezinu puta do cvora neighbour
        g.distances[neighbour.first] = g.distances[tmp.second] + neighbour.second;
        // Dodajemo cvor neighbour zajedno sa novom tezinom puta u heap
        heap.push(std::make_pair(g.distances[neighbour.first], neighbour.first));
      }
    }
  }

  // Stek na koji smestamo cvorove iz putanje jer rekonstruisanjem kroz roditeljske cvorove dobijamo putanju unazad
  std::stack<int> path;

  // Idemo sve do pocetnog cvora ciji je roditelj i dalje -1, i dodajemo sve na stek
  while (g.parents[v] != -1) {
    path.push(v);
    // Azuriramo cvor v
    v = g.parents[v];
  }

  // Dodajemo i pocetni cvor na stek
  path.push(v);

  // Velicina steka
  int n = path.size();

  int node;
  // Dok god ima elemenata na steku uzimamo onaj sa vrha i ispisujemo ga
  while (n > 0) {
    node = path.top();

    // Skidamo element sa steka
    path.pop();

    n--;

    if (n > 0)
      std::cout << node << " -> ";
    else
      std::cout << node << "\n";
  }
}

int main ()
{
  Graph g;

  initialize_graph(g, 9);

  add_edge(g, 0, 1, 4);
  add_edge(g, 0, 7, 8);
  add_edge(g, 1, 7, 11);
  add_edge(g, 1, 2, 8);
  add_edge(g, 2, 8, 3);
  add_edge(g, 2, 3, 7);
  add_edge(g, 7, 8, 7);
  add_edge(g, 7, 6, 1);
  add_edge(g, 8, 6, 6);
  add_edge(g, 2, 5, 4);
  add_edge(g, 6, 5, 2);
  add_edge(g, 3, 5, 14);
  add_edge(g, 3, 4, 9);
  add_edge(g, 4, 5, 10);

  dijkstra(g, 0, 8);

  return 0;
}
