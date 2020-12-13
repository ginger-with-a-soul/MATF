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
  // Vektor koji cuva vremena posecivanja cvorova u DFS obilasku
  std::vector<int> times;
  // Vektor koji cuva lower times za sve cvorove. Lower time je zapravo minamlna vrednost time-a za sve susedne cvorove cvora u
  std::vector<int> lower_times;
  // Stek na koji se smestaju cvorovi
  std::stack<int> stack;
  // Vektor koji nam govori za svaki od cvorova da li je u steku ili ne
  std::vector<bool> in_stack;
  // Promenljiva koja predstavlja vreme koje se dodeljuje svakom od cvorova
  int time;
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

  // Na pocetku je time 0
  g.time = 0;

  // Alociramo mesto za V int vrednosti koje ce cuvati vremena obilaska cvorova. Na pocetku svi imaju vreme obilaska -1
  g.times.resize(V, -1);
  
  // Alociramo mesto za V int vrednosti koje ce cuvati lower times obilaska cvorova. Na pocetku svi imaju lower times -1
  g.lower_times.resize(V, -1);
 
  // Alociramo mesto za V bool vrednosti koje ce cuvati podatak o tome da li je cvor na steku vec. Na pocetku nijedan cvor nije na steku
  g.in_stack.resize(V, false);
}

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
}

// Obilazak grafa u dubinu
void DFS(Graph &g, int u)
{
  // Trenutnom cvoru postavljamo i vreme obilaska i lower time na time
  g.times[u] = g.lower_times[u] = g.time;

  // Uvecavamo time za sledeci cvor
  g.time++;

  // Dodajemo cvor na stek
  g.stack.push(u);

  // Kazemo da cvor koji trenutno razmatramo jeste u steku
  g.in_stack[u] = true;

  // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
  // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
  auto begin = g.adjacency_list[u].begin();
  auto end = g.adjacency_list[u].end();

  while (begin != end) {
    // Ako cvor nije vec posecen posecujemo ga
    if (g.times[*begin] == -1) {
      DFS(g, *begin);

      // Ako imamo suseda ciji je lower time manji od lower time-a trenutnog cvora onda azuriramo i lower time trenutnog cvora
      g.lower_times[u] = std::min(g.lower_times[*begin], g.lower_times[u]);
    }
    // Ako je sused vec posecen i nalazi se u steku, mozda je njegovo lower time manje od lower time-a cvora u, pa samim tim treba azurirati lower time cvora u
    else if (g.in_stack[*begin] == true) {
      g.lower_times[u] = std::min(g.lower_times[u], g.times[*begin]);
    }

    // Krecemo se kroz kolekciju
    begin++;
  }

  // Ako smo dosli do korena neke komponente, indikator za to nam je da je njegov time jednak lower_time-u
  if (g.times[u] == g.lower_times[u]) {
    // Idemo "beskonacno"
    while (1) {
      // Uzimamo element sa vrha steka
      int v = g.stack.top();

      // Uklanjamo element sa vrha steka
      g.stack.pop();

      // Ispisujemo cvor
      std::cout << v << " ";

      // Kazemo da element vise nije u steku
      g.in_stack[v] = false;

      // Ako smo dosli do korena, onda smo obisli ceu komponentu i samo izlazimo iz "beskonacne" petlje
      if (v == u) {
        std::cout << "\n";
        break;
      }
    }
  }
}

int main ()
{
  Graph g;

  initialize_graph(g, 8);

  add_edge(g, 0, 1);
  add_edge(g, 0, 2);
  add_edge(g, 1, 0);
  add_edge(g, 1, 3);
  add_edge(g, 2, 3);
  add_edge(g, 3, 4);
  add_edge(g, 3, 5);
  add_edge(g, 4, 2);
  add_edge(g, 4, 5);
  add_edge(g, 4, 6);
  add_edge(g, 5, 7);
  add_edge(g, 6, 5);
  add_edge(g, 7, 6);

  // add_edge(g, 0, 1);
  // add_edge(g, 0, 2);
  // add_edge(g, 0, 7);
  // add_edge(g, 1, 3);
  // add_edge(g, 1, 4);
  // add_edge(g, 2, 5);
  // add_edge(g, 4, 6);
  // add_edge(g, 5, 8);
  // add_edge(g, 6, 1);
  // add_edge(g, 8, 0);

  // add_edge(g, 0, 1);
  // add_edge(g, 1, 2);
  // add_edge(g, 2, 3);
  // add_edge(g, 3, 1);
  // add_edge(g, 3, 0);

  // add_edge(g, 0, 1);
  // add_edge(g, 1, 2);
  // add_edge(g, 2, 3);
  // add_edge(g, 3, 0);
  // add_edge(g, 5, 0);
  // add_edge(g, 5, 4);

  DFS(g, 0);

  return 0;
}
