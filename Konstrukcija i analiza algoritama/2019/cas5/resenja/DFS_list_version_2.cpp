#include <iostream>
#include <vector>

// DFS pretraga grafa koji je zadat pravom listom povezanosti
// Kako nemamo klase u ovom primeru, kao argumente saljemo listu susedstva i vector posecenih cvorova
void DFS(int v, std::vector<int> &adjacency_list, std::vector<bool> &visited)
{
  // Cvor koji trenutno obradjujemo oznacavamo kao posecen
  visited[v] = true;

  // Ispisujemo trenutni cvor
  std::cout << v << " ";

  int n;

  // Ukoliko nam je sledeci element u listi manji od trenutnog, to znaci da krecemo sa nabrajanjem suseda za cvorove, i to znaci da smo dosli do poslednjeg cvora grafa
  // Njegovi susedi se u listi nalaze od pozicije adjacency_list[v] do kraja liste. Zato razmatramo 2 slucaja, jedan kada imamo poslednji cvor u grafu i drugi gde imamo
  // ostale cvorove
  if (adjacency_list[v + 1] < adjacency_list[v])
    // Ukoliko je u pitanju poslednji cvor u grafu, idemo od adjacency_list[v] do kraja liste
    n = adjacency_list.size();
  else
    // Ukoliko nije u pitanju poslednji cvor u grafu, idemo od adjacency_list[v] do adjacency_list[v + 1] gde pocinju susedi narednog cvora
    n = adjacency_list[v + 1];

  // Prolazimo kroz sve susede trenutnog cvora
  for (int i = adjacency_list[v]; i < n; i++) {
    // Sused koji nije posecen se posecuje rekurzivno
    if (!visited[adjacency_list[i]])
      DFS(adjacency_list[i], adjacency_list, visited);
  }
}

int main ()
{
  int v;

  std::cin >> v;

  std::vector<int> adjacency_list = { 4, 6, 7, 9, 1, 2, 2, 0, 3, 3 };

  std::vector<bool> visited(4);

  std::fill(visited.begin(), visited.end(), false);

  DFS(v, adjacency_list, visited);

  std::cout << std::endl;

  return 0;
}
