#include <iostream>
#include <vector>
#include <stack>

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
  // Struktura stek u koju cemo smestati cvorove grafa
  std::stack<int> stack;
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
}

// Funkcija koja dodaje granu u -> v u graf, i menja ulazni stepen cvora
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

  // TEK NAKON STO SMO OBILSI SVE NJEGOVE SUSEDE dodajemo element na stek, kako se on nalazi vise na steku bice i ranije ispisivan, jer njegovi susedi
  // (ka kojima vode grane) "zavise" od njega
  g.stack.push(u);
}

void topological_sorting(Graph &g)
{
  // Prolazimo kroz sve cvorove grafa
  for (int i = 0; i < g.V; i++)
    // Za svaki cvor koji nije posecen pozivamo DFS pretragu
    if (!g.visited[i])
      DFS(g, i);

  // Skidamo elemente sa steka redom dok god ih ima i ispisujemo ih
  while (g.stack.size()) {
    // top() vraca element sa vrha steka ali ga ne sklanja
    std::cout << g.stack.top() << " ";
    // pop() skida element sa vrha steka
    g.stack.pop();
  }

  std::cout << "\n";
}


int main ()
{
  Graph g;

  initialize_graph(g, 6);

  // add_edge(g, 5, 2);
  // add_edge(g, 5, 0);
  // add_edge(g, 4, 0);
  // add_edge(g, 4, 1);
  // add_edge(g, 2, 3);
  // add_edge(g, 3, 1);

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
