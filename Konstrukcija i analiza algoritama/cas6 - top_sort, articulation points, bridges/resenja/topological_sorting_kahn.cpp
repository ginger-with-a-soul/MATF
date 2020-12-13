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
  // Vektor koji cuva ulazne stepene za svaki od cvorova
  std::vector<int> in_degrees;
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
  // Imamo V cvorova pa nam je vektor ulazinh stepena velicine V. Na pocetku svi cvorovi imaju ulazni stepen 0
  g.in_degrees.resize(V, 0);
}

// Funkcija koja dodaje granu u -> v u graf, i menja ulazni stepen cvora
void add_edge(Graph &g, int u, int v)
{
  // Sused cvora u je cvor v
  g.adjacency_list[u].push_back(v);

  // Kada dodamo granu u -> v znaci da se ulazni stepen cvora v povecava za 1
  g.in_degrees[v]++;
}

void topological_sorting(Graph &g)
{
  // Red koji koristimo za cuvanje cvorova koje treba obraditi
  std::queue<int> nodes;

  // Odmah dodamo sve cvorove ciji je ulazni stepen 0
  for (int i = 0; i < g.V; i++)
    if (!g.in_degrees[i]) {
      nodes.push(i);
    }
    
  // Pomocni cvor u koji smestamo ono sto izvucemo iz reda
  int tmp;

  while (nodes.size()) {
    // Uzimamo cvor sa pocetka reda
    tmp = nodes.front();

    // Skidamo cvor sa pocetka reda
    nodes.pop();

    // Ispisujemo cvor koji trenutno razmatramo
    std::cout << tmp << " ";

    // Prolazimo kroz sve cvorove koji su susedni cvoru tmp, smanjujemo im ulazni stepen, i onda ako je neki dosao do ulaznog stepena 0, znaci da smo obisli sve njegove
    // susede tako da se i on moze dodati na kraj reda
    for (int node : g.adjacency_list[tmp]) {
      g.in_degrees[node]--;

      if (!g.in_degrees[node])
        nodes.push(node);
    }
  }

  std::cout << "\n";
}

int main ()
{
  Graph g;

  initialize_graph(g, 6);

  add_edge(g, 0, 1);
  add_edge(g, 1, 4);
  add_edge(g, 2, 4);
  add_edge(g, 3, 0);
  add_edge(g, 3, 2);
  add_edge(g, 5, 2);
  add_edge(g, 5, 4);

  topological_sorting(g);

  return 0;
}
