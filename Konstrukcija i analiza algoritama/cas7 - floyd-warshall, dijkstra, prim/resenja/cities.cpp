#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <stack>

#define INFINITY INT_MAX

// Struktura kojom se predstavlja graf
struct Graph
{
  // Broj cvorova grafa
  int V;
  int **matrix;
  // Vektor koji ce nam govoriti koji cvorovi su ukljuceni u minimalno razapinjuce stablo
  std::vector<bool> included_in_MST;
  // Vektor koji govori koji je roditeljski cvor svakog od cvorova
  std::vector<int> parents;
  // Vektor koji za svaki cvor govori o vrednosti grane koja se ukljucuje u MST a povezuje njega i njegovog roditelja
  std::vector<int> edges;
};

// Funkcija koja sluzi da inicijalizuje strukturu graf (konstruktor)
// Da bismo menjali graf moramo po referenci da saljemo strukturu
// Funkcija kao argument ima samo broj cvorova grafa
void initialize_graph (Graph &g, int V)
{
  // Broj cvorova grafa je jednak prosledjenom argumentu
  g.V = V;
  // Alociramo prostor za niz nizova, tj matricu, u C++-u moramo da imamo eksplicitno kastovanje u (int **), odsnosno (int *) inace se g++ buni
  g.matrix = (int **)malloc(V * sizeof(int *));
  // Svaki od elemenata matrice je novi niz, pa se alocira i memorija za njih
  for (int i = 0; i < g.V; i++)
    g.matrix[i] = (int *)calloc(sizeof(int), V);  
  // Alociramo prostor za V bool vrednosti. Na pocetku kazemo da nijedan cvor nije ukljucen u MST
  g.included_in_MST.resize(V, false);
  // Alociramo prostor za v int vrednosti. Na pocetku kazemo da su svi roditelji -1
  g.parents.resize(V, -1);
  // Alociramo prostor za v int vrednosti. Na pocetku kazemo da su sve "minimalne grane" INFINITY
  g.edges.resize(V, INFINITY);
}

// Funkcija za nalazenje grane najmanje tezine koja nije vec ubacena u MST
int min_edge_not_included(Graph &g)
{
  // Minimum je INFINITY a indeks minimuma -1 na pocetku
  int min = INFINITY;
  int min_index = -1;

  // Idemo kroz sve cvorove
  for (int i = 0; i < g.V; i++)
    // Ako cvor vec nije ukljucen u MST, i ako je grana koja vodi ka njemu manja od trenutnog minimuma, menjamo minimum i pamtimo koji je to cvor koji sledeci treba
    // obraditi, tj koji je to cvor ka kome vodi minimalna grana
    if (g.included_in_MST[i] == false && g.edges[i] < min) {
      min_index = i;
      min = g.edges[i];
    }

  return min_index;
}

// Funkcija koja dodaje grane u -> v i v -> u u graf. Obe grane su tezine weight
void add_edge(Graph &g, int u, int v, int weight)
{
  g.matrix[u][v] = weight;
  g.matrix[v][u] = weight;
}

// Primov algoritam
void prim(Graph &g, int u)
{
  // Tezina grane do pocetnog cvora je 0
  g.edges[u] = 0;

  int node;

  // MST ima ukupno V - 1 grana pa petlja ide do V - 1
  for (int i = 0; i < g.V - 1; i++) {
    // Uzimamo cvor do koga treba da odemo, tj onaj ka kome vodi grana minimalne tezine koja nije vec u MST-u
    node = min_edge_not_included(g);

    // Ubacimo cvor u MST
    g.included_in_MST[node] = true;

    // Prodjemo kroz sve susede cvora ndoe i eventualno azuriramo vrednosti grana koje vode ka njima, ukoliko je vrednost grane manja od trenutno minimalne grane koja ide
    // ka odgovarajucem susedu
    for (int v = 0; v < g.V; v++) {
      if (g.matrix[node][v] && g.included_in_MST[v] == false && g.matrix[node][v] < g.edges[v]) {
        g.parents[v] = node;
        g.edges[v] = g.matrix[node][v];
      }
    }
  }

  // Cena MST-a je 0 na pocetku
  int cost = 0;

  // Idemo kroz sve cvorove i dodajemo tezine grana koje su dodate u MST, to su bas grane koje povezuju svaki cvor i sa cvorom parents[i]. Jedino ne racunamo u jer je
  // njegov roditelj -1 i on je pocetni cvor do kog ne vodi nijedna grana
  for (int i = 0; i < g.V; i++)
    if (i != u)
      cost += g.edges[i];

  // Ispisujemo ukupnu cenu povezivanja svih gradova, odnosno sumu svih grana MST-a
  std::cout << cost << std::endl;
}

int main ()
{
  Graph g;

  initialize_graph(g, 5);

  add_edge(g, 0, 1, 1);
  add_edge(g, 0, 2, 5);
  add_edge(g, 0, 3, 10);
  add_edge(g, 0, 4, 4);
  add_edge(g, 1, 2, 2);
  add_edge(g, 1, 4, 1);
  add_edge(g, 2, 3, 4);

  prim(g, 0);

  return 0;
}
