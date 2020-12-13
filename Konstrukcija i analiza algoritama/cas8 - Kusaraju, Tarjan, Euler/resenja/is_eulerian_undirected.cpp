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
  // Lista posecenih cvorova. 
  std::vector<bool> visited;
  // Vektor koji ce nam govoriti koliki je ulazni stepen svakog od cvorova
  // Graf je neusmeren, pa ce nam ovde biti uracunate i ulazne i izlazne grane, jer su nam u ovom slucaju jednake
  std::vector<int> degrees;
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
  // Alociramo prostor. Postavljamo stepene na 0
  g.degrees.resize(V, 0);
}

// Funkcija koja dodaje grane u -> v i v - > u u graf
void add_edge(Graph &g, int u, int v)
{
  // Sused cvora u je cvor v
  g.adjacency_list[u].push_back(v);

  // Sused cvora u je cvor v
  g.adjacency_list[v].push_back(u);

  // Povecavamo ulazni, odnosno izlazni stepen za oba cvora
  g.degrees[u]++;
  g.degrees[v]++;
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

// Funkcija koja proverava da li je graf povezan, tj da li su svi cvorovi koji imaju stepen veci od 0 povezani
bool is_connected(Graph &g)
{
  // Cvor iz koga krecemo DFS
  int start_node;

  // Prvo nadjemo cvor koji ima stepen veci od 0, uzmemo bilo koji takav cvor i iz njega mozemo da pokrenemo DFS, tako bi trebalo da prodjemo kroz sve cvorove
  // koji imaju stepen razlicit od 0. Ako neki ne obidjemo graf nam nije povezan i vracamo false
  for (int i = 0; i < g.V; i++)
    if (g.adjacency_list[i].size() > 0)
      start_node = i;

  // Pokrecemo DFS
  DFS(g, start_node);

  // Idemo kroz sve cvorove
  for (int i = 0; i < g.V; i++)
    // Ako ima neki neposeceni koji ima stepen veci od 0, vracamo false
    if (g.visited[i] == false && g.degrees[i] > 0)
      return false;

  return true;
}

// Funkcija koja broji koliko imamo cvorova neparnog stepena u grafu
int num_of_odd_vertices(Graph &g)
{
  // Broj cvorova neparnog stepena
  int count_odd = 0;

  // Ako imamo neki cvor sa ukupnim neparnim stepenom uvecavamo broj takvih cvorova
  for (int i = 0; i < g.V; i++)
    if (g.degrees[i] % 2)
      count_odd++;

  return count_odd;

  // return count_if(g.degrees.begin(), g.degrees.end(), [](int degree){ return degree % 2; });
}

// Funkcija koja vraca 0 ako graf nije Ojlerov, 1 ako graf ima Ojlerov put, ali nema Ojlerov ciklus i 2 ako ima Ojlerov ciklus
int is_eulerian(Graph &g)
{
  int count_odd = num_of_odd_vertices(g);

  // Ako imamo vise od dva cvora sa neparnim stepenima vracamo 0, tj graf nije Ojlerov
  if (count_odd > 2)
    return 0;

  // Ako graf nije povezan, odnosno ako neke cvorove stepena veceg od 0 koji nisu povezani vracamo da graf nije Ojlerov
  if (!is_connected(g))
    return 0;

  // Vracamo informaciju o tome da li graf ima Ojlerov ciklus ili samo put, ako ima 0 cvorova neparnog stepena onda ima ciklus, inace put
  return count_odd == 0 ? 2 : 1;
}

int main ()
{
  Graph g;

  initialize_graph(g, 5);

  // Ciklus
  add_edge(g, 0, 1);
  add_edge(g, 1, 2);
  add_edge(g, 2, 0);

  // Nije Ojlerov
  // add_edge(g, 0, 1);
  // add_edge(g, 1, 2);
  // add_edge(g, 1, 4);
  // add_edge(g, 2, 3);

  // Put
  // add_edge(g, 0, 1);
  // add_edge(g, 0, 2);
  // add_edge(g, 0, 3);
  // add_edge(g, 1, 2);
  // add_edge(g, 1, 3);
  // add_edge(g, 2, 3);
  // add_edge(g, 2, 4);
  // add_edge(g, 3, 4);

  int eulerian = is_eulerian(g);

  std::cout << (eulerian == 0 ? "G is not Eulerian!" : (eulerian == 1 ? "G has Eulerian path!" : "G has Eulerian cycle!")) << std::endl;

  return 0;
}
