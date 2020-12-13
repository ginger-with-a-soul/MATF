#include <iostream>
#include <vector>
#include <climits>

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
  // Kazemo da je minimalni broj grana na pocetku najveci moguci broj koji cuva int
  g.min_num_of_edges = INT_MAX;
}

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
}

// DFS koji prima pocetni, krajnji cvor i broj grana na trenutnom putu
void DFS(Graph &g, int u, int v, int current_num_of_edges)
{
	// Ako smo dosli do ciljnog cvora proveravamo koliki je broj grana na tom put, ako je manji od trenutnog minimuma, onda je to i novi minimum
	if (u == v) {
	  if (current_num_of_edges < g.min_num_of_edges)
	    g.min_num_of_edges = current_num_of_edges;

	  // Izlazimo iz rekurzije
	  return ;
	}

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
	    // Kazemo da je broj grana za 1 veci nego do sad, jer se krecemo ka novom cvoru, znaci imamo jos jednu granu na putu
	    DFS(g, *begin, v, current_num_of_edges + 1);

	  // Krecemo se kroz kolekciju
	  begin++;
	}

	// Ovo je neophodan uslov, jer mi zelimo zapravo da nadjemo sve putanje od u do v da bismo videli koja ima najmanji broj cvorova, tako da kada se zavrsi deo putanje
	// kroz jedan cvor on treba da postane neposecen jer mozda postoji drugi put koji ide kroz taj cvor
	g.visited[u] = false;
}

// Getter za minimalan broj grana
int get_min_num_of_edges(const Graph &g)
{
return g.min_num_of_edges;
}



int main ()
{
  int u, v;

  std::cin >> u >> v;

  Graph g;

  initialize_graph(g, 5);

  add_edge(g, 0, 1);
  add_edge(g, 1, 0);
  add_edge(g, 0, 4);
  add_edge(g, 4, 0);
  add_edge(g, 1, 2);
  add_edge(g, 2, 1);
  add_edge(g, 2, 4);
  add_edge(g, 4, 2);
  add_edge(g, 2, 3);
  add_edge(g, 3, 2);
  add_edge(g, 3, 4);
  add_edge(g, 4, 3);

  // add_edge(g, 0, 1);
  // add_edge(g, 0, 4);
  // add_edge(g, 1, 2);
  // add_edge(g, 2, 4);
  // add_edge(g, 2, 3);
  // add_edge(g, 3, 4);

  DFS(g, u, v, 0);

  std::cout << get_min_num_of_edges(g) << std::endl;

  return 0;
}
