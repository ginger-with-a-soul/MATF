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
    return p1.second > p2.second;
  }
};

// Struktura kojom se predstavlja graf
struct Graph
{
  // Lista susedstva. Imamo vector parova gde je prvi element cvor ka kome void grana a drugi element tezina grane
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Vektor koji ce da cuva tezinu puta od pocetnog cvora do svakog odgovarajuceg cvora
  std::vector<int> distances;
  // Vektor koji ce nam govoriti do kog cvora smo vec nasli najkraci put
  std::vector<bool> path_found;
  // Vektor koji cuva policijske stanice
  std::vector<int> police_stations;
  // Pravimo min-heap za cuvanje svih cvorova grafa. Svaki cvor heap-a ce biti cvor kao i najkrace rastojanje do njega koje je do tad nadjeno
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> heap;
};

// Funkcija koja sluzi da inicijalizuje strukturu graf (konstruktor)
// Da bismo menjali graf moramo po referenci da saljemo strukturu
// Funkcija kao argument ima samo broj cvorova grafa
void initialize_graph (Graph &g, int V)
{
  // Broj cvorova grafa je jednak prosledjenom argumentu
  g.V = V;
  // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
  g.adjacency_list.resize(V);
  // Alociramo prostor za V integer-a. Na pocetku kazemo da su svi udaljeni beskonacno
  g.distances.resize(V, INFINITY);
  // Alociramo prostor za V bool vrednosti. Na pocetku kazemo da ni do jednog cvora nemamo put
  g.path_found.resize(V, false);
}

// Funkcija koja dodaje grane u -> v  i v -> u u graf
void add_edge(Graph &g, int u, int v)
{
  // Funkcija std::make_pair kreira par vrednosti koje se prosledjuju kao argumenti
  // Sused cvora u je cvor v, a tezina je weight
  g.adjacency_list[u].push_back(v);
  // Sused cvora v je cvor u a tezina je weight
  g.adjacency_list[v].push_back(u);
}

void dijkstra(Graph &g)
{
  std::pair<int, int> tmp;

  // Dok god ima elemenata u heap-u
  while (!g.heap.empty()) {
    // Uzimamo koreni element heap-a
    tmp = g.heap.top();

    // Skidamo element sa vrha heap-a
    g.heap.pop();

    // Kako moze da se desi da smo neki cvor vise puta ubacili u heap, ako opet naidjemo na cvor koji je vec obradjen, tj do kog smo nasli najkraci put, necemo ponovo
    // da ga obradjujemo
    if (g.path_found[tmp.first])
      continue;

    // Kada udjemo u cvor znamo da smo nasli najkraci put do njega pa to i kazemo
    g.path_found[tmp.first] = true;

    // Prolazimo kroz listu suseda cvora tmp
    // tmp je par ciji je prvi element cvor a drugi cena najkraceg puta do tog cvora, tako da svuda gde nam treba cvor imamo tmp.first
    for (int neighbour : g.adjacency_list[tmp.first]) {
      // Ako preko cvora tmp imamo kraci put do nekog suseda onda azuriramo najkraci put do tog suseda i dodajemo ga na heap
      if (g.distances[neighbour] > g.distances[tmp.first] + 1) {
        // Azuriramo udaljenost cvora neighbour
        g.distances[neighbour] = g.distances[tmp.first] + 1;
        // Dodajemo cvor neighbour zajedno sa novom tezinom puta u heap
        g.heap.push(std::make_pair(neighbour, g.distances[neighbour]));
      }
    }
  }
}

void closest_police_stations(Graph &g)
{
  // U heap dodajemo sve one gradove koji imaju policijske stanice, i njihova udaljenost do najblize stanice je 0
  for (int station : g.police_stations) {
    g.heap.push(std::make_pair(station, 0));
    g.distances[station] = 0;
  }

  dijkstra(g);

  // Samo ispisujemo udaljenosti za svaki od gradova do najblize policijske stanice
  for (int i = 0; i < g.V; i++)
    std::cout << "Closest police station from city " << i << " is " << g.distances[i] << " kilometers away" << std::endl;
}

void add_police_station(Graph &g, int station)
{
  // Dodajemo policijsku stanicu u vektor policijskih stanica
  g.police_stations.push_back(station);
}


int main ()
{
  Graph g;

  initialize_graph(g, 7);

  add_edge(g, 0, 1);
  add_edge(g, 0, 5);
  add_edge(g, 1, 2);
  add_edge(g, 1, 5);
  add_edge(g, 2, 3);
  add_edge(g, 2, 4);
  add_edge(g, 2, 5);
  add_edge(g, 3, 4);
  add_edge(g, 2, 6);

  add_police_station(g, 0);
  add_police_station(g, 4);

  closest_police_stations(g);

  return 0;
}
