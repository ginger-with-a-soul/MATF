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

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
}

// DFS koji prima pocetni krajnji cvor i vector u koji ce smestati rezultat, odnosno putanju od u do v
// Obratiti paznju da NE SME biti slato kao referenca, jer cemo onda stalno menjat isti vector, a nama zapravo treba za svaki put odvojen vector (detaljnije objasnjenje na casu, ili konsultacije)
void DFS(Graph &g, int u, int v, std::vector<int> result)
{
	// Ako smo dosli do cilja, dodajemo i njega u result i ispisujemo put od u do v
	if (u == v) {
	  result.push_back(v);
	  
	  int i;
	  for (i = 0; i < result.size() - 1; i++)
	    std::cout << result[i] << " -> ";

	  std::cout << result[i] << std::endl;

	  // Kraj rekurzije
	  return ;
	}

	// Kazemo da je cvor koji trenutno obradjujemo vec posecen
	g.visited[u] = true;

	// Ubacujemo cvor u result, kako bismo pamtili put kojim smo isli
	result.push_back(u);

	// Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
	// Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
	auto begin = g.adjacency_list[u].begin();
	auto end = g.adjacency_list[u].end();

	while (begin != end) {
	  // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
	  // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
	  // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
	  if (!g.visited[*begin])
	    DFS(g, *begin, v, result);

	  // Krecemo se krzo kolekciju
	  begin++;
	}

	// Ovo je neophodan uslov, jer mi zelimo zapravo da nadjemo sve putanje od u do v, tako da kada se zavrsi deo putanje kroz jedan cvor on treba da postane neposecen
	// jer mozda postoji drugi put koji ide kroz taj cvor
	g.visited[u] = false;
}

int main ()
{
  int u, v;

  std::cin >> u >> v;

  Graph g;

  initialize_graph(g, 4);

  add_edge(g, 0, 1);
  add_edge(g, 0, 2);
  add_edge(g, 0, 3);
  add_edge(g, 2, 0);
  add_edge(g, 2, 1);
  add_edge(g, 1, 3);

  std::vector<int> result;

  DFS(g, u, v, result);

  return 0;
}
