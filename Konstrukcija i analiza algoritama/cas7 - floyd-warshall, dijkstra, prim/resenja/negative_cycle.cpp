#include <iostream>
#include <cstdlib>
#include <climits>

#define INFINITY 9999

// Struktura kojom se predstavlja graf
struct Graph
{
  // Broj cvorova grafa
  int V;
  // Matrica susedstva
  int **matrix;
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
  for (int i = 0; i < V; i++)
    g.matrix[i] = (int *)calloc(sizeof(int), V);

  // Kazemo da je svaki element matrice matrix jednak INFINITY osim elemenata na dijagonali koji su 0
  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++) {
      if (i == j)
        g.matrix[i][j] = 0;
      else
        g.matrix[i][j] = INFINITY;
    }
}

// Dodajemo granu izmedju u i v koja je tezine weight
void add_edge(Graph &g, int u, int v, int weight)
{
  g.matrix[u][v] = weight;
}

void floyd_warshall(Graph &g)
{
  // Uzimamo svaki od cvorova kao srednji cvor
  for (int k = 0; k < g.V; k++) { 
    // Uzimamo svaki od cvorova kao pocetni cvor
    for (int i = 0; i < g.V; i++) { 
      // Uzimamo svaki od cvorova kao kranji cvor
      for (int j = 0; j < g.V; j++) { 
        // Ako je udaljenost pocetnog do krajnjeg cvora preko srednjeg manja od trenutne udaljenosti, idemo preko srednjeg cvora i azuriramo vrednost puta od pocetnog do
        // krajnjeg cvora
        if (g.matrix[i][j] > g.matrix[i][k] + g.matrix[k][j])
          g.matrix[i][j] = g.matrix[i][k] + g.matrix[k][j];
      }
    }
  }

  // Idemo kroz matricu povezanosti koja cuva najkrace puteve i samo vidimo da li je neki cvor do sebe "negativno udaljen" sto nam oznacava negativni ciklus
  for (int i = 0; i < g.V; i++)
    if (g.matrix[i][i] < 0) {
      std::cout << "YES!\n";
      return ;
    }

  std::cout << "NO!\n";
}

int main ()
{
  Graph g;

  initialize_graph(g, 4);

  add_edge(g, 0, 1, 1);
  add_edge(g, 1, 2, -1);
  add_edge(g, 2, 3, -1);
  add_edge(g, 3, 0, -1);

  floyd_warshall(g);

  return 0;
}
