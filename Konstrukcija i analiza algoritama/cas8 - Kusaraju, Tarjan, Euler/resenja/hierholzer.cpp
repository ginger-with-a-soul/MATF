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
  // Stek na koji smestamo trenutnu putanju dok ne dodjemo do cvora koji treba da se stavi u konacnu putanju
  std::stack<int> stack;
  // Vektor koji nam predstavlja konacnu putanju, tj Ojlerov ciklus
  std::vector<int> eulerian_path;
};

// Funkcija koja sluzi da inicijalizuje strukturu graf (konstruktor)
// Da bismo menjali graf moramo po referenci da saljemo strukturu
// Funkcija kao argument ima samo broj cvorova grafa
void initialize_graph (Graph &g, int V)
{
  // Broj cvorova grafa je jednak prosledjenom argumentu
  g.V = V;

  // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
  g.adjacency_list.resize(V);
}

// Funkcija koja dodaje granu u -> v u graf
void add_edge(Graph &g, int u, int v)
{
  // Sused cvora u je cvor v
  g.adjacency_list[u].push_back(v);
}

void hierholzer (Graph &g)
{
  // Stavljamo cvor iz koga krecemo u trenutnu putanju
  g.stack.push(0);
  // Trenutni cvor koji razmatramo je bas pocetni
  int v = 0;

  // Pomocna promenljiva za cuvanje cvorova
  int tmp;

  // Dok god na steku ima cvorova
  while (g.stack.size()) {
    // Ako iz trenutnog cvora imamo bar jos jednu granu
    if (g.adjacency_list[v].size()) {

      // Dodajemo cvor v na stek
      g.stack.push(v);

      // Uzimamo jednu granu iz cvora v, pamtimo ka kom cvoru ona vodi i izbacujemo je
      tmp = g.adjacency_list[v].back();
      g.adjacency_list[v].pop_back();

      // Naredni cvor koji se razmatra je bas tmp, tj cvor u koji smo otisli iz cvora v
      v = tmp;
    }
    // Ako iz trenutnog cvora nema vise grana
    else {
      // Ako smo dosli ovde znaci da nema vise grana iz ovog cvora i on treba da bude dodat u Ojlerov ciklus
      g.eulerian_path.push_back(v);

      // Vracamo se nazad u cvor iz koga smo dosli i njega razmatramo, trazimo novu granu ili ako ih vise nema, dodajemo njega u putanju itd.
      v = g.stack.top();
      g.stack.pop();
    }
  }

  int i;

  // Nakon sto smo prosli kroz sve cvorove ispisujemo putanju koju smo nasli
  for (i = g.eulerian_path.size() - 1; i >= 1; i--)
    std::cout << g.eulerian_path[i] << " -> ";

  std::cout << g.eulerian_path[i] << std::endl;
}

int main ()
{
  Graph g;

  initialize_graph(g, 5);

  add_edge(g, 0, 1);
  add_edge(g, 1, 2);
  add_edge(g, 1, 3);
  add_edge(g, 2, 0);
  add_edge(g, 3, 4);
  add_edge(g, 4, 1);

  // add_edge(g, 0, 1);
  // add_edge(g, 0, 2);
  // add_edge(g, 1, 1);
  // add_edge(g, 1, 3);
  // add_edge(g, 1, 3);
  // add_edge(g, 2, 0);
  // add_edge(g, 2, 1);
  // add_edge(g, 2, 4);
  // add_edge(g, 3, 2);
  // add_edge(g, 3, 5);
  // add_edge(g, 4, 5);
  // add_edge(g, 5, 2);

  hierholzer(g);

  return 0;
}
