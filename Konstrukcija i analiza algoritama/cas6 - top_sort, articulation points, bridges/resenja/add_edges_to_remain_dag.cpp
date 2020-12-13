#include <iostream>
#include <vector>
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
  // Vektor koji cuva ulazne stepene za svaki od cvorova
  std::vector<int> in_degrees;
  // Vektor koji cuva cvorove u redosledu u kom se oni nalaze u topoloskom sortiranju
  std::vector<int> topological;
  // Vektor koji ce cuvati sve grane, sluzi samo za proveru resenja, da vidimo da li smo dobili graf bez ciklusa
  std::vector<std::pair<int, int>> edges;
  // Vektor koji ce cuvati samo grane koje smo dodali, sluzi samo za proveru resenja, da vidimo da li smo dobili graf bez ciklusa i da vidimo koje su to grane dodate
  std::vector<std::pair<int, int>> added_edges;
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
}

// Funkcija koja dodaje granu u -> v u graf, i menja ulazni stepen cvora
void add_edge(Graph &g, int u, int v)
{
  // Sused cvora u je cvor v
  g.adjacency_list[u].push_back(v);

  // Kada dodamo granu u -> v znaci da se ulazni stepen cvora v povecava za 1
  g.in_degrees[v]++;

  // Kreiramo par (u, v) kao indikator da grana u -> v postoji u grafu
  std::pair<int, int> p(u, v);

  g.edges.push_back(p);
}

void topological_sorting(Graph &g)
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
    std::cout << tmp << " ";

    // Dodajemo cvor u rezultat
    g.topological.push_back(tmp);

    // Prolazimo kroz sve cvorove koji su susedni cvoru tmp, smanjujemo im ulazni stepen, i onda ako je neki dosao do ulaznog stepena 0, znaci da smo obisli sve njegove
    // susede tako da se i on moze dodati na kraj reda
    for (int node : g.adjacency_list[tmp]) {
      g.in_degrees[node]--;

      if (!g.in_degrees[node])
        nodes.push(node);
    }
  }
}

// Modifikacija DFS-a koja proverava da li usmereni graf ima ciklus (zadatak sa 5. casa)
bool DFS(Graph &g, int u)
{
  // Kazemo da je cvor koji trenutno obradjujemo vec posecen
  g.visited[u] = true;

  // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
  // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
  auto begin = g.adjacency_list[u].begin();
  auto end = g.adjacency_list[u].end();

  while (begin != end) {
    // Ako smo dosli do cvora koji smo vec posetili na trenutnom putu onda znaci da imamo ciklus i vracamo true. Obratiti paznju na deo NA TRENUTNOM PUTU,
    //kako imamo rekurziju i ako nam je graf 0 -> 1, 1 -> 2, 0 -> 2 on nema ciklus. Jedan put je 0 -> 1 -> 2 a drugi 0 -> 1 -> 2.
    // Da gledamo uopsteno da li je cvor posecen a ne NA TRENUTNOM PUTU onda bismo kada idemo 0 -> 2 naisli na cvor koji je vec posecen i onda bi bilo da imamo ciklus,
    // zato svaki put kada zavrsimo rekurzivni poziv kazemo da je cvor u neposecen, tj visited[u] = false;
    if (g.visited[*begin]) {
      return true;
    }
    // Ako nam neki rekurzivi poziv vrati true to znaci da smo u nekom podgrafu nasli ciklus pa samo vracamo true
    else if (DFS(g, *begin)) {
      return true;
    }

    // Krecemo se kroz kolekciju
    begin++;
  }

  // Objasnjenje gore
  g.visited[u] = false;
  // Nemamo ciklus na ovom putu, ako na nekom drugom putu naidjemo na ciklus to cemo u while petlji detektovati i vratiti true
  return false;
}

// Funkcija koja ce nam dodati grane u graf
void add_edges(Graph &g)
{
  topological_sorting(g);

  // Prolazimo kroz redosled cvorova u topoloskom sortiranju
  for (int i = 0; i < g.V; i++) {
    // Prolazimo kroz sve susede cvora koji trenutno razmatramo u topoloskom sortiranju i kazemo da su vec poseceni, kako ne bismo dodavali grane ka njima ponovo
    for (int y : g.adjacency_list[g.topological[i]])
      g.visited[y] = true;

    // Prolazimo kroz sve cvorove koji su posle cvora i u topoloskom redosledu i ako ka njima nema grane dodajemo je
    for (int j = i + 1; j < g.V; j++) {
      if (!g.visited[g.topological[j]]) {
        std::pair<int, int> p(g.topological[i], g.topological[j]);
        g.edges.push_back(p);
        g.added_edges.push_back(p);
      }
      // Sve cvorove vracamo na false, jer cemo za neke od njih dodati grane iz drugih cvorova
      g.visited[g.topological[j]] = false;
    }
  }

  // Koristimo modifikaciju DFS-a sa 5. casa da proverimo da li imamo ciklus, tj da li smo ispravno usmerili neusmeren grane
  if (DFS(g, 0))
    std::cout << "Has a cycle\n";
  else
    std::cout << "Doesn't have a cycle\n";

  // Ispisujemo sve grane koje smo dobili
  std::cout << "All edges:\n";
  // Prolazimo kroz listu svih grana kako bismo proverili da li zaista nemamo cikluse
  for (auto p : g.edges)
    std::cout << p.first << " -> " << p.second << std::endl;

  // Ispisujemo samo one grane koje smo dodali
  std::cout << "Added edges:\n";
  // Prolazimo kroz listu svih grana kako bismo proverili da li zaista nemamo cikluse
  for (auto p : g.added_edges)
    std::cout << p.first << " -> " << p.second << std::endl;
}

int main ()
{
  Graph g;

  initialize_graph(g, 6);

  add_edge(g, 2, 3);
  add_edge(g, 3, 1);
  add_edge(g, 4, 0);
  add_edge(g, 4, 1);
  add_edge(g, 5, 0);
  add_edge(g, 5, 2);

  add_edges(g);

  return 0;
}
