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
    // Ovde jos dodatno proveravamo da li grana postoji, tj da li nije obrisana
    if (*begin != -1 && !g.visited[*begin])
      DFS(g, *begin);
    // Krecemo se kroz kolekciju
    begin++;
  }
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
}

// Funkcija koja vraca neki cvor neparnog stepena
int find_node_with_odd_degree(Graph &g)
{
  // Idemo kroz sve cvorove
  for (int i = 0; i < g.V; i++) {
    // Ako je stepen neparan vracamo cvor
    if (g.degrees[i] % 2)
      return i;
  }
}

// Funkcija koja vraca neki cvor parnog stepena
int find_node_with_even_degree(const Graph &g)
{
  // Idemo kroz sve cvorove
  for (int i = 0; i < g.V; i++) {
    // Ako je stepen paran i nije 0 vracamo cvor
    if (g.degrees[i] % 2 == 0 && g.degrees[i])
      return i;
  }
}

void remove_edge(Graph &g, int u, int v)
{
  // Nalazimo gde se u listi povezanosti cvora u nalazi cvor v i na tu poziciju stavljamo -1, kao oznaku da je grana uklonjena
  auto it_u = std::find(g.adjacency_list[u].begin(), g.adjacency_list[u].end(), v);
  *it_u = -1;

  // Nalazimo gde se u listi povezanosti cvora v nalazi cvor u i na tu poziciju stavljamo -1, kao oznaku da je grana uklonjena
  auto it_v = std::find(g.adjacency_list[v].begin(), g.adjacency_list[v].end(), u);
  *it_v = -1;
}

// Funkcija koja proverava da li grana moze biti uklonjena. Funkcija gleda da li je grana most. Ako je most i ako je jedina grana iz cvora u onda je sve okej
// ali ako je most a ima jos grana iz cvora u, onda ne smemo da uzmemo most, tj necemo je ukloniti
bool is_valid_edge(Graph &g, int u, int v)
{
  // Brojimo koliko imamo grana od cvora u, prebrojimo sve one koje nisu izbacene. Ako imam tacno jednu granu onda je u -> v jedina grana i nju onda smemo da
  // izbacimo. Ako imamo vise od jedne grane, onda gledamo da li je u -> v most. Ako jeste most ideo dalje u pretragu, jer ona ne sme biti izbacena, ako nije
  // most mozemo da je izbacimo
  int count_edges = std::count_if(g.adjacency_list[u].begin(), g.adjacency_list[u].end(), [](int x){ return x != -1; });

  if (count_edges == 1)
    return true;

  // Uklanjamo grane u -> v i v -> u
  remove_edge(g, u, v);

  // Postavimo sve cvorove na neposecene jer imamo vise DFS obilazaka grafa, kako bismo uvek imali "sveze" podatke, azuriramo ovaj vektor
  std:fill(g.visited.begin(), g.visited.end(), false);

  // Pokrecemo DFS iz u
  DFS(g, u);

  // Brisemo pojavu -1 iz vektora povezanosti cvora u. Ovim smo uklonili jednu granu koja je bila obrisana. I onda dodajemo granu u -> v.
  g.adjacency_list[u].erase(std::find(g.adjacency_list[u].begin(), g.adjacency_list[u].end(), -1));
  // Brisemo pojavu -1 iz vektora povezanosti cvora v. Ovim smo uklonili jednu granu koja je bila obrisana. I onda dodajemo granu v -> u.
  g.adjacency_list[v].erase(std::find(g.adjacency_list[v].begin(), g.adjacency_list[v].end(), -1));
  // Vracamo grane u -> v i v -> u
  add_edge(g, u, v);

  // Ako nismo posetili cvor v znaci da je grana u -> v bila most i da ne smemo da je uklanjamo
  if (!g.visited[v]) {
    return false;
  }

  // Inace vracamo true, sto znaci da grana u -> v moze da bude izbacena
  return true;
}

void print_euler_path_or_cycle(Graph &g, int u)
{
  // Idemo kroz sve susede cvora u
  for (int v : g.adjacency_list[u]) {
    // Ako grana postoji tj nije obrisana i ako moze biti obrisana
    if (v != -1 && is_valid_edge(g, u, v)) {
      std::cout << u << " -> " << v << std::endl;
      remove_edge(g, u, v);
      print_euler_path_or_cycle(g ,v);
    }
  }
}

void fleury(Graph &g)
{
  // Brojimo koliko ima cvorova koji su neparnog stepena
  int count_odd = num_of_odd_vertices(g);

  // Cvor iz koga se krece;
  int start_node;

  // Ako nema nijednog, mozemo da krenemo iz bilo kog cvora koji nema stepen 0
  if (count_odd == 0) {
    start_node = find_node_with_even_degree(g);
    print_euler_path_or_cycle(g, start_node);
  }
  // Ako imamo 2 cvora koja su neparnog stepena krecemo iz bilo kog od ta dva
  else if (count_odd == 2) {
    start_node = find_node_with_odd_degree(g);
    print_euler_path_or_cycle(g, start_node);
  }
}

int main ()
{
  Graph g;

  initialize_graph(g, 5);

  // Put
  // add_edge(g, 0, 1);
  // add_edge(g, 0, 2);
  // add_edge(g, 1, 2);
  // add_edge(g, 2, 3);

  // Ciklus
  // add_edge(g, 0, 1);
  // add_edge(g, 1, 2);
  // add_edge(g, 2, 0);

  add_edge(g, 0, 1);
  add_edge(g, 0, 2);
  add_edge(g, 0, 3);
  add_edge(g, 1, 2);
  add_edge(g, 1, 3);
  add_edge(g, 2, 3);
  add_edge(g, 2, 4);
  add_edge(g, 3, 4);

  fleury(g);

  return 0;
}
