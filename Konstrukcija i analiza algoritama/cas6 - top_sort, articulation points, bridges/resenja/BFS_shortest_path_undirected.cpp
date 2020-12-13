#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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
  // Vektor koji cuva za svaki cvor cvor iz koga smo dosli u njega
  std::vector<int> parents;
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
  // Alociramo mesto za V int vrednosti koje ce cuvati roditelje cvorova. Za sve cvorove na pocetku kazemo da nemaju roditelja, tj da im je roditelj -1
  g.parents.resize(V, -1);
}

// Funkcija koja dodaje granu u -> v u graf G
void add_edge(Graph &g, int u, int v)
{
	// Sused cvora u je cvor v
	g.adjacency_list[u].push_back(v);
  // Sused cvora v je cvor u
  g.adjacency_list[v].push_back(u);
}

// Obilazak grafa u sirinu
void BFS(Graph &g, int u, int v)
{
  // Red koji koristimo za cuvanje cvorova grafa
  std::queue<int> nodes;

  // Dodajemo pocetni cvor iz koga krecemo
  nodes.push(u);

  g.visited[u] = true;

  // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
  int pom;

  // Idemo dok god imamo cvorova u redu
  while (!nodes.empty()) {
    // Uzimamo cvor sa pocetka reda
    /********* C++ deo *********/
    // Metod front() samo uzima element sa pocetka reda ali ga i ne uklanja
    pom = nodes.front();
    // Skidamo cvor sa pocetka reda
    /********* C++ deo *********/
    // Metod pop() skida element sa pocetka reda
    nodes.pop();

    // Ako je cvor koji trenutno razmatramo bas ciljni cvor znaci da smo nasli put od u do v, ujedno je taj put i najkraci
    if (pom == v) {
      return ;
    }

    // Uzimamo iteratore na pocetak i kraj vektora koji cuva susede trenutnog cvora
    auto begin = g.adjacency_list[pom].begin();
    auto end = g.adjacency_list[pom].end();

    while (begin != end) {
      // Ukoliko nismo vec posetili cvor zelimo i njega da posetimo, pa ga dodajemo u red kako bi u nekoj od narednih iteracija bio obradjen
      if (!g.visited[*begin]) {
        g.visited[*begin] = true;
        g.parents[*begin] = pom;
        nodes.push(*begin);
      }
      // Krecemo se kroz kolekciju
      begin++;
    }
  }
}

// Funkcija koja ispisuje najkraci put od cvor u do cvora v ukoliko on postoji
void print_shortest_path(Graph &g, int u, int v)
{
  // Koristimo strukturu stek, jer cemo mi zapravo uzimati roditelje cvorova unazad. Neka nam je ciljni cvor 7 a pocetni 0, i najkraci put medju njima 0 -> 3 -> 7.
  // Mi znamo da je roditelj cvora 7 3 a roditelj cvora 3 0. Tim redosledom ih i obilazimo. Da bismo imali ispis 0 -> 3 -> 7, smestamo na stek roditelje, i onda
  // ih skidamo sa steka i ispisujemo
  std::stack <int> path;

  // BFS koji ce popuniti listu roditelja
  BFS(g, u, v);

  if (g.parents[v] == -1) {
    std::cout << "Ne postoji put!" << std::endl;
    return ;
  }

  // Stavljamo krajnji cvor svakako u putanju
  path.push(v);

  // Dok ne naidjemo na cvor iz kog smo krenuli (znamo da je njegov roditelj -1), krecemo se kroz roditelje, odnosno idemo unazad, od v do u
  while (g.parents[v] != -1) {
    v = g.parents[v];
    path.push(v);
  }

  int n = path.size();

  int x;

  // Dok god ima elemenata na steku ispisujemo ih
  while (n) {
    // Uzimamo element sa vrha steka
    x = path.top();
    // Skidamo element sa vrha steka
    path.pop();
    // Ako nije poslednji (ciljni cvor v) ispisujemo x ->
    if (n > 1)
      std::cout << x << " -> ";
    // Inace ispisujemo samo posldenji cvor na putanji
    else
      std::cout << x << std::endl;
    n--;
  }
}


int main ()
{
  Graph g;

  initialize_graph(g, 8);

  add_edge(g, 0, 1);
  add_edge(g, 0, 3);
  add_edge(g, 1, 2);
  add_edge(g, 3, 4);
  add_edge(g, 3, 7);
  add_edge(g, 4, 5);
  add_edge(g, 4, 6);
  add_edge(g, 4, 7);
  add_edge(g, 5, 6);
  add_edge(g, 6, 7);

  int u, v;

  std::cin >> u >> v;

  print_shortest_path(g, u, v);

  return 0;
}
