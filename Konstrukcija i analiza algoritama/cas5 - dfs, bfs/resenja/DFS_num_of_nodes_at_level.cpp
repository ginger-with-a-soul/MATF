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
  // Promenljiva koja oznacava broj cvorova na odgovarajucem nivou
  int num_of_nodes;
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
  // Na pocetku kazemo da nemamo nijedan cvor na odredjenom nivou
  g.num_of_nodes = 0;
}

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
}

void DFS(Graph &g, int u, int level, int current_level)
{
  // Kazemo da je cvor koji trenutno obradjujemo vec posecen
  g.visited[u] = true;

  // Ako je nivo na kome je trenutni cvor jednak trazenom nivou uvecavamo broj cvorova na tom nivou
  if (current_level == level)
    g.num_of_nodes++;

  // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
  // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
  auto begin = g.adjacency_list[u].begin();
  auto end = g.adjacency_list[u].end();

  while (begin != end) {
    // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
    // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
    // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
    if (!g.visited[*begin])
      // Pozivamo rekurziju i kazemo da je trenutni nivo za 1 veci, jer idemo dublje kroz stablo
      DFS(g, *begin, level, current_level + 1);

    // Krecemo se kroz kolekciju
    begin++;
  }
}

// Getter za broj cvorova na odredjenom nivou
int get_num_of_nodes(const Graph &g)
{
  return g.num_of_nodes;
}

int main()
{
    Graph g;

    initialize_graph(g, 8);

    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 0, 7);
    add_edge(g, 4, 6);
    add_edge(g, 4, 5);
    add_edge(g, 4, 2);
    add_edge(g, 7, 3);
 
    int level;

    std::cin >> level;

    DFS(g, 0, level, 0);

    std::cout << get_num_of_nodes(g) << std::endl;

    return 0;
}
