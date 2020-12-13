#include <iostream>
#include <vector>

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
  // Promenljiva koja predstavlja minimalan broj grana na putu od u do v
  int min_num_of_edges;
  // Promenljiva koja oznacava broj komponenti grafa
  int number_of_components;

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
      // Na pocetku kazemo da nemamo nijednu komponentu
  g.number_of_components = 0;
}

// Dodajemo granu u -> v i v -> u, posto je graf neusmeren, mozemo to ovako da oznacimo
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora v je cvor u
	g.adjacency_list[v].push_back(u);
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
}

// Obilazak grafa u dubinu
void DFS(Graph &g, int u)
{
  // Kazemo da je cvor koji trenutno obradjujemo vec posecen
  g.visited[u] = true;

  // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
  // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
  auto begin = g.adjacency_list[u].begin();
  auto end = g.adjacency_list[u].end();

  while (begin != end) {
    // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
    // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
    // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
    if (!g.visited[*begin])
      DFS(g, *begin);
    // Krecemo se kroz kolekciju
    begin++;
  }
}

int num_of_components(Graph &g)
{
  // Kada se vratimo iz DFS-a obisli smo sve cvorove u komponenti grafa, tako da idemo samo kroz sve cvorove i oni koji nisu oznaceni pripadaju nekoj komponenti koju nismo
  // obisli, pa obilazimo tu komponentu i uvecavamo broj komponenti
  for (int i = 0; i < g.V; i++)
    if (!g.visited[i]) {
      g.number_of_components++;
      DFS(g, i);
    }

  return g.number_of_components;
}

int main ()
{
  Graph g;

  initialize_graph(g, 6);

  add_edge(g, 0, 1);
  add_edge(g, 0, 2);
  add_edge(g, 1, 2);
  add_edge(g, 2, 0);
  add_edge(g, 2, 3);
  add_edge(g, 3, 3);
  add_edge(g, 4, 5);
  add_edge(g, 4, 4);
  add_edge(g, 5, 4);

  std::cout << num_of_components(g) << "\n";

  return 0;
}
