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
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Promenljiva koja cuva broj ciklusa duzine n
  int num_of_cycles;
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
  // Broj ciklusa na pocetku je 0
  g.num_of_cycles = 0;
}

// Funkcija koja dodaje grane u -> v i v -> u u graf (posto je neusmeren)
void add_edge(Graph &g, int u, int v)
{
  // Sused cvora u je cvor v
  g.adjacency_list[u].push_back(v);

  // Sused cvora v je cvor u
  g.adjacency_list[v].push_back(u);
}
 
// Obilazak grafa u dubinu
void DFS(Graph &g, int u, int start, int n)
{
  // Kazemo da je cvor koji trenutno obradjujemo vec posecen
  g.visited[u] = true;

  // Ako smo nasli put duzine n - 1 i dosli do cvora u proveravamo da li iz cvora u postoji grana ka cvoru iz koga smo krenuli, ako postoji super, imamo ciklus
  // inace nemamo ciklus i samo oznacavamo cvor u kao neoznacen zbog narednih iteracija i zavrsavamo rekurziju
  if (n == 0) {
    if (std::find(g.adjacency_list[u].begin(), g.adjacency_list[u].end(), start) != g.adjacency_list[u].end()) {
      g.num_of_cycles++;
    }

    g.visited[u] = false;
    return ;
  }

  // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
  // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
  auto begin = g.adjacency_list[u].begin();
  auto end = g.adjacency_list[u].end();

  while (begin != end) {
    // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
    // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
    // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
    // Kao dodatne argumente saljemo jos cvor iz koga smo krenuli kao i n - 1, jer sa trazimo put za 1 manje duzine
    if (!g.visited[*begin])
      DFS(g, *begin, start, n - 1);
    // Krecemo se kroz kolekciju
    begin++;
  }

  // Nakon sto obidjemo sve susede cvora stavljamo na false visited[u] jer mozda postoji drugi ciklus koji sadrzi u, i on ce biti razmotren kasnije
  g.visited[u] = false;

}

int num_of_cycles_of_size_n(Graph &g, int n)
{
  // Kada se vratimo iz DFS-a obisli smo sve cvorove u komponenti grafa, tako da idemo samo kroz sve cvorove i oni koji nisu oznaceni pripadaju nekoj komponenti koju nismo
  // obisli, pa obilazimo tu komponentu i uvecavamo broj komponenti
  for (int i = 0; i < g.V - (n - 1); i++) {
    DFS(g, i, i, n - 1);
    g.visited[i] = true;
  }

  return g.num_of_cycles / 2;
}


int main ()
{
  int n;

  std::cin >> n;

  // add_edge(g, 0, 1);
  // add_edge(g, 0, 3);
  // add_edge(g, 1, 2);
  // add_edge(g, 1, 4);
  // add_edge(g, 2, 3);
  // add_edge(g, 2, 3);
  // add_edge(g, 3, 4);

  Graph g;

  initialize_graph(g, 7);

  add_edge(g, 0, 1);
  add_edge(g, 1, 2);
  add_edge(g, 2, 3);
  add_edge(g, 3, 0);
  add_edge(g, 3, 4);
  add_edge(g, 4, 6);
  add_edge(g, 6, 5);
  add_edge(g, 5, 3);

  std::cout << num_of_cycles_of_size_n(g, n) << "\n";

  return 0;
}
