#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
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
  // Vektor koji cuva ulazne stepene za svaki od cvorova
  std::vector<int> in_degrees;
  // Promenljiva koja oznacava da je ciklus pronadjen
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
  // Imamo V cvorova pa nam je vektor ulazinh stepena velicine V. Na pocetku svi cvorovi imaju ulazni stepen 0
  g.in_degrees.resize(V, 0);
  // Na pocetku pretpostavljamo da nema ciklusa
  g.found = false;
}

// Funkcija koja dodaje granu u -> v u graf, i menja ulazni stepen cvora
void add_edge(Graph &g, int u, int v)
{
  // Sused cvora u je cvor v
  g.adjacency_list[u].push_back(v);

  // Kada dodamo granu u -> v znaci da se ulazni stepen cvora v povecava za 1
  g.in_degrees[v]++;
}

void topological_sorting(Graph &g, std::vector<int> &result)
{
  // Red koji koristimo za cuvanje cvorova koje treba obraditi
  std::queue<int> nodes;

  // Odmah dodamo sve cvorove ciji je ulazni stepen 0
  for (int i = 0; i < g.V; i++)
    if (!g.in_degrees[i]) {
      nodes.push(i);
    }
    
  // Pomocni cvor u koji smestamo ono sto izvucemo iz reda
  int tmp;

  while (nodes.size()) {
    // Uzimamo cvor sa pocetka reda
    tmp = nodes.front();

    // Skidamo cvor sa pocetka reda
    nodes.pop();

    // Dodajemo cvor u rezultat
    result.push_back(tmp);

    // Prolazimo kroz sve cvorove koji su susedni cvoru tmp, smanjujemo im ulazni stepen, i onda ako je neki dosao do ulaznog stepena 0, znaci da smo obisli sve njegove
    // susede tako da se i on moze dodati na kraj reda
    for (int node : g.adjacency_list[tmp]) {
      g.in_degrees[node]--;

      if (!g.in_degrees[node])
        nodes.push(node);
    }
  }
}

void DFS(Graph &g, int u, std::vector<int> &result, int start_node)
{
  // Ako smo usli u vec posecen cvor ovo znaci da smo nasli kraj ciklusa, tako da samo ispisujemo krajnji cvor i zavrsavamo funkciju
  if (g.visited[u] && u == start_node) {
    result.push_back(u);
    g.found = true;
    return ;
  }

  // Oznacavamo da je trenutni cvor posecen
  g.visited[u] = true;

  result.push_back(u);

  // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
  // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
  auto begin = g.adjacency_list[u].begin();
  auto end = g.adjacency_list[u].end();

  while (begin != end) {
    // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
    // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
    // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
    if (!g.found)
      DFS(g, *begin, result, start_node);
    // Krecemo se kroz kolekciju
    begin++;
  }
}

void find(Graph &g)
{
  // Vektor result koji ce cuvati redosled cvorova u topoloskom sortitanju grafa
  std::vector<int> result;

  // Pokrenemo algoritam za topolosko sortiranje
  topological_sorting(g, result);

  // Promenljiva koja oznacava da li ispisujemo ciklus ili topoloski poredak
  bool topological = true;

  // Idemo kroz sve cvorove i ako naidjemo na cvor koji ima stepen veci od 0, znaci da topolosko sortiranje ne postoji odnosno da imamo ciklus, stavljamo topological na
  // false da to oznacimo
  for (int i = 0; i < g.V; i++)
    if (g.in_degrees[i]) {
      topological = false;
    }

  // Ako treba da ispisemo topoloski poredak, ispisujemo sve iz vektora result
  if (topological) {
    std::cout << "Topological sorting: ";
    for (int x : result)
      std::cout << x << " ";
    std::cout << "\n";
    return ;
  }

  std::cout << "Cycle: ";

  result.clear();

  // Ako imamo ciklus, pozivamo DFS iz prvog cvora ciji je ulazni stepen > 0 i u DFS-u zapravo nalazimo ciklus koji postoji
  for (int i = 0; i < g.V; i++)
    if (g.in_degrees[i] != 0) {
      DFS(g, i, result, i);

      int j;

      for (j = 0; j < result.size() - 1; j++)
        std::cout << result[j] << " -> " ;

      std::cout << result[j] << "\n";

      return ;
    }
}

int main ()
{
  Graph g;

  initialize_graph(g, 6);

  // add_edge(g, 0, 2);
  // add_edge(g, 2, 1);
  // add_edge(g, 1, 3);
  // add_edge(g, 3, 4);
  // add_edge(g, 4, 1);
  // add_edge(g, 4, 2);
  
  add_edge(g, 0, 1);
  add_edge(g, 1, 4);
  add_edge(g, 2, 4);
  add_edge(g, 3, 0);
  add_edge(g, 3, 2);
  add_edge(g, 5, 2);
  add_edge(g, 5, 4);

  // add_edge(g, 0, 1);
  // add_edge(g, 1, 2);
  // add_edge(g, 2, 3);
  // add_edge(g, 3, 4);
  // add_edge(g, 4, 3);
  // add_edge(g, 4, 5);
  // add_edge(g, 5, 6);

  find(g);

  return 0;
}
