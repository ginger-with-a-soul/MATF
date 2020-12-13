#include <iostream>
#include <vector>
#include <algorithm>

// Struktura kojom se predstavlja graf
struct Graph
{
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova
  std::vector<bool> visited;
};

// Funkcija koja sluzi da inicijalizuje strukturu graf (konstruktor)
// Da bismo menjali graf moramo po referenci da saljemo strukturu
// Funkcija kao argument ima samo broj cvorova grafa
void initialize_graph (Graph &g, int V)
{
  // Broj cvorova grafa je jednak prosledjenom argumentu
  g.V = V;
  // Alociramo mesto za V bool vrednosti koje ce cuvati posecene cvorove. Na pocetku nijedan cvor nije posecen
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

Graph reverse_edges(Graph &g)
{
  // pravimo novi graf sa takodje V cvorova
  Graph g_pom;

  initialize_graph(g_pom, g.V);

  // Idemo kroz sve cvorove grafa
  for (int i = 0; i < g.V; i++)
    // Idemo kroz sve susede i-tog cvora
    for (int u : g.adjacency_list[i])
      // Dodajemo suprotnu granu u odnosnu na onu koja postoji. Ako smo npr imali liste povezanosti
      // 0 -> 1 -> 2
      // 1 -> 2
      // 2 -> 0
      // Spoljasnja petlja po i ide redom kroz ove liste, unutrasnja po u ide kroz svaku listu, tako da ako je i == 0, idemo kroz listu suseda cvora i
      // I onda znamo da imamo grane i -> u, zato u novi graf g dodajemo granu u -> v
      add_edge(g_pom, u, i);

  // Vracamo graf g
  return g_pom;
}

// Funkcija koja broji neposecene cvorove
int count_unvisited_nodes(const Graph &g)
{
  // Brojac za sve elemente koji nisu poseceni
  int counter = 0;

  for (int i = 0; i < g.V; i++)
    if (g.visited[i] == false)
      counter++;

  // Samo vracamo brojac
  return counter;

  // return std::count_if(g.visited.begin(), g.visited.end(), [](bool visited) { return visited == false; });
}

bool kosaraju(Graph &g)
{
  // Pokrecemo DFS iz cvora 0
  DFS(g, 0);

  // Prebrojavamo koliko imamo elemenata u vektoru visited za koje vazi da je vrednost false, tj brojimo koliko ima cvorova koji nisu poseceni. Ako do nekog cvora nismo
  // stigli, znaci da graf nije jako povezan.
  if (count_unvisited_nodes(g) > 0)
    return false;

  // Pravimo novi graf za koji cemo opet pokrenuti DFS
  Graph g_pom = reverse_edges(g);

  // Pozivamo DFS za novi graf
  DFS(g_pom, 0);

  // Proveravamo koliko u njemu ima neposecenih cvorova nakon DFS-a
  if (count_unvisited_nodes(g_pom) > 0)
    return false;

  // Vracamo potvrdan odgovor na pitanje da li je graf jako povezan
  return true;
}

int main ()
{
  Graph g;

  initialize_graph(g, 5);

  // Jeste
  add_edge(g, 0, 1);
  add_edge(g, 1, 2);
  add_edge(g, 2, 3);
  add_edge(g, 3, 0);
  add_edge(g, 2, 4);
  add_edge(g, 4, 2);

  // Nije
  // add_edge(g, 0, 1);
  // add_edge(g, 1, 2);
  // add_edge(g, 2, 3);

  std::cout << (kosaraju(g) ? "Graph is strongly connected!\n" : "Graph is not strongly connected!\n");

  return 0;
}
