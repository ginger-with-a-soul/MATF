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
  // Vektor koji nam cuva samo boju za svaki od cvorova
  std::vector<int> colors;
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
  // Alociramo mesto za V int vrednosti koje ce cuvati boje cvorova. Za sve cvorove na pocetku kazemo da nemaju boju, tj da im je boja -1
  g.colors.resize(V, -1);
}

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
  // Sused cvora v je cvor u
  g.adjacency_list[v].push_back(u);
}

// DFS ce nam ovde vracati bool. Ako je graf bipartitan vracace true inace false
bool DFS(Graph &g, int u, int color)
{
  // Kazemo da je cvor koji trenutno obradjujemo vec posecen
  g.visited[u] = true;

  // Dodeljujemo pocetnom cvoru jednu boju. Boje su iz skupa [0,1]
  g.colors[u] = color;

  // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
  // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
  auto begin = g.adjacency_list[u].begin();
  auto end = g.adjacency_list[u].end();

  while (begin != end) {
    // Ukoliko se desi da cvor koji zelimo da posetimo vec ima dodeljenu boju i da je ta boja ista kao i kod cvora v to znaci da imamo 2 suseda koja imaju istu boju,
    // tj pripadaju istoj particiji onda vracamo false, jer smo sigurni da nam graf u tom slucaju nije bipartitan
    if (g.colors[*begin] == g.colors[u]) {
      return false;
    }

    // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno, i to sa drugom bojom. Ako je u imao boju 0, svi
    // njegovi susedi treba da imaju 1 i obratno
    // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
    // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
    if (!g.visited[*begin]) {
      // Ukoliko nam se iz nekog od rekurzivnih poziva vraca false, imamo dokaz da graf nije bipartitan, i odmah vracamo false, nema potrebe dalje bilo sta proveravati
      if (!DFS(g, *begin, !color))
        return false;
    }
    // Krecemo se kroz kolekciju
    begin++;
  }

  // Ukoliko dodjemo do ovde znaci da nismo nasli nigde da graf nije bipartitan pa vracamo true
  return true;
}

int main ()
{
  Graph g;

  initialize_graph(g, 6);

  add_edge(g, 0, 1);
  add_edge(g, 1, 2);
  add_edge(g, 2, 3);
  add_edge(g, 3, 4);
  add_edge(g, 4, 5);
  add_edge(g, 5, 0);
  // Dodati ovu granu u graf i videti rezultat
  add_edge(g, 2, 0);


  std::cout << DFS(g, 0, 0) << "\n";

  return 0;
}
