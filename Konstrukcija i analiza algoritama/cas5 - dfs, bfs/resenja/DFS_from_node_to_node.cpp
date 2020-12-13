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
  // Promenljiva koja nam govori da li smo pronasli ciljni cvor
  bool found;
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
  // Postavljamo promenljivu found na false odnosno nismo uspeli da nadjemo cvor na samom pocetku pretrage
  g.found = false;

}

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
}

// Pretraga u dubinu koja pamti sve cvorove kojima smo isli do ciljnog cvora. u je pocetni, v ciljni cvor a result cuva bas putanju od u do v kojom smo isli
bool DFS(Graph &g, int u, int v, std::vector<int> &result)
{
  // Ako smo nasli cvor
  if (u == v) {
    // Ubacujemo u result i ciljni cvor
    result.push_back(v);
    // Kazemo da smo nasli cvor
    g.found = true;
    // Izlazimo iz rekurzije
    return true;
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
    bool ret_val = false;
    
    // Ako nismo vec posetili cvor ali i ako nismo nasli put idemo dalje, ako smo vec nasli put od u do v, sacuvan je u result i necemo dalje da idemo nigde
    if (!g.visited[*begin] && !g.found)
      ret_val = DFS(g, *begin, v, result);

    if (ret_val)
      return true;

    result.pop_back();
    
    // Krecemo se kroz kolekciju
    begin++;
  }

  return false;
}

// Getter za promenljivu found
bool get_found(const Graph &g)
{
  return g.found;
}

int main ()
{
  int u, v;

  std::cin >> u >> v;

  Graph g;

  initialize_graph(g, 5);

  add_edge(g, 0, 1);
  add_edge(g, 1, 2);
  add_edge(g, 1, 3);
  add_edge(g, 3, 4);

  std::vector<int> result;

  DFS(g, u, v, result);

  // Ukoliko je found ostalo false znaci da nema puta od u do v
  if (!get_found(g))
    std::cout << "Nema puta!\n";
  // Inace ispisujemo put od u do v
  else {
    int i;
    for (i = 0; i < result.size() - 1; i++)
      std::cout << result[i] << " -> ";

    std::cout << result[i] << std::endl;
  }

  return 0;
}
