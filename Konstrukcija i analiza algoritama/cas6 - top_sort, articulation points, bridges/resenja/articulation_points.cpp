#include <iostream>
#include <vector>
#include <set>

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
  // Vektor koji cuva cvorove roditelje za svaki od cvorova
  std::vector<int> parents;
  // Vektor koji cuva vremena posecivanja cvorova u DFS obilasku
  std::vector<int> times;
  // Vektor koji cuva lower times za sve cvorove. Lower time je zapravo minamlna vrednost time-a za sve susedne cvorove cvora u
  std::vector<int> lower_times;
  // Vektor koji cuva artikulacione tacke
  std::set<int> articulation_points;
  // Promenljiva koja predstavlja vreme koje se dodeljuje svakom od cvorova
  int time;
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
  // Alociramo mesto za V int vrednosti koje ce cuvati roditelje cvorova. Na pocetku svi imaju roditelja -1
  g.parents.resize(V, -1);
  // Na pocetku je time 0
  g.time = 0;
  // Alociramo mesto za V int vrednosti koje ce cuvati vremena obilaska cvorova. Na pocetku svi imaju vreme obilaska -1
  g.times.resize(V, -1);
  // Alociramo mesto za V int vrednosti koje ce cuvati lower times obilaska cvorova. Na pocetku svi imaju lower times -1
  g.lower_times.resize(V, -1);
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
void DFS(Graph &g, int u)
{
  // Kazemo da je cvor koji trenutno obradjujemo vec posecen
  g.visited[u] = true;

  // Trenutnom cvoru postavljamo i vreme obilaska i lower time na time
  g.times[u] = g.lower_times[u] = g.time;

  // Uvecavamo time za sledeci cvor
  g.time++;

  // Broj potomaka cvora na pocetku je 0
  int children = 0;

  // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
  // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
  auto begin = g.adjacency_list[u].begin();
  auto end = g.adjacency_list[u].end();

  while (begin != end) {
    // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
    // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
    // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
    if (!g.visited[*begin]) {

      // Roditelj cvora koji cuva iterator je cvor u
      g.parents[*begin] = u;

      DFS(g, *begin);

      // Ako smo nasli na neposecenog suseda, znaci da je broj potomaka cvora v treba da se poveca za 1
      children++;

      // Ako imamo suseda ciji je lower time manji od lower time-a trenutnog cvora onda azuriramo i lower time trenutnog cvora
      g.lower_times[u] = std::min(g.lower_times[*begin], g.lower_times[u]);

      // Ukoliko je cvor koreni cvor i ima 2 ili vise nepovezanih cvorova onda on jeste artikulaciona tacka
      if (g.parents[u] == -1 && children > 1)
        g.articulation_points.insert(u);

      // Ako cvor nije koreni cvor ali je njegovo vreme <= lower time-u bilo kog njegovog suseda, onda on jeste artikulaciona tacka
      if (g.parents[u] != -1 && g.times[u] <= g.lower_times[*begin])
        g.articulation_points.insert(u);
    }
    // Ako je sused vec posecen i nije roditelj cvora u, mozda je njegovo lower time manje od lower time-a cvora u, pa samim tim treba azurirati lower time cvora u
    else if (*begin != g.parents[u]) {
      g.lower_times[u] = std::min(g.lower_times[u], g.times[*begin]);
    }

    // Krecemo se kroz kolekciju
    begin++;
  }
}

void find_articulation_points(Graph &g)
{
  DFS(g, 3);

  for (int x : g.articulation_points)
    std::cout << x << " ";

  std::cout << std::endl;

  // for (int x : g.lower_times)
  //   std::cout << x << " ";
  // std::cout << "\n";
}

int main ()
{
  Graph g;

  initialize_graph(g, 8);

  add_edge(g, 0, 1);
  add_edge(g, 0, 2);
  add_edge(g, 1, 2);
  add_edge(g, 2, 3);
  add_edge(g, 3, 4);
  add_edge(g, 4, 5);
  add_edge(g, 4, 6);
  add_edge(g, 5, 6);
  add_edge(g, 5, 7);
  add_edge(g, 2, 6);

  find_articulation_points(g);

  return 0;
}
