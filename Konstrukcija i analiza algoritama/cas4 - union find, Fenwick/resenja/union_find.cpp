#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

// FUnkcija za pronalzenje predstavnika skupa kome element pripada
// Znamo da je roditelj predstavnika on sam, tako da krenemo od elementa za koji se pitamo kom skupu pripada
// krecemo se uz stablo dok ne dodjemo do korena, tj predstavnika za koga vazi da je parent[x] == x
int find(int x, const std::vector<int> &parent)
{
	// Dok ne dodjemo do korena
	while (x != parent[x]) {
		// Penjemo se uz stablo
		x = parent[x];
	}

	// Vracamo predstavnika, tj oznaku skupa kome pocetni element pripada
	return x;
}

// Kreiranje unije 2 skupa. Ako su iste visine oba stabla (skupa) onda mozemo da ih nadovezemo na bilo koji nacin i samo povecavamo rang onog skupa na koji lepimo drugi skup 
void make_union(int x, int y, std::vector<int> &parent, std::vector<int> &rank)
{
	// Trazimo za oba elementa predstavnike kako bismo znali za koja 2 skupa treba naci uniju
	int fx = find(x, parent), fy = find(y, parent);

	// Ako je skup kome x pripada manjeg ranga njegov pokazivac preusmeravamo na drugi skup (lepimo to stablo na drugo)
	if (rank[fx] < rank[fy])
		parent[fx] = fy;
	// Ako je skup kome y pripada manjeg ranga njegov pokazivac preusmeravamo na drugi skup (lepimo to stablo na drugo)
	else if (rank[fx] > rank[fy])
		parent[fy] = fx;
	// Ako su istog ranga mozemo bilo koji skup da nalepimo na drugi, ali onaj na koji se lepi menja i rang za 1
	else {
		parent[fx] = fy;
		rank[fy]++;
	}
}

int main ()
{
	int n, m;
  std::cin >> n >> m;

  // Kreiramo vektor grana oblika trenutak gasenja - cvor - cvor
  std::vector<std::tuple<int, int, int>>edges(m);
  for(int i = 0; i < m; i++)
  	std::cin >> std::get<0>(edges[i]) >> std::get<1>(edges[i]) >> std::get<2>(edges[i]);

  // Sortiramo grane opadajuce po vremenu gasenja
  std::sort(edges.begin(), edges.end(), [](const auto &x, const auto &y){ return std::get<0>(x) > std::get<0>(y); });

  std::vector<int> parent(n), rank(n);
  // Svaki cvor je svoj roditelj na pocetku
  for (int i = 0; i < n; i++)
  	parent[i] = i;


  for(auto &edge : edges) {
  	int x = std::get<1>(edge), y = std::get<2>(edge);

		// Ukoliko 2 cvora pripadaju istom ciklusu doci ce do kratkog spoja i ispisujemo vrednost koja predstavlja trenutak gasenja odgovarajuce grane    
    if(find(x, parent) == find(y, parent)) {
			std::cout << std::get<0>(edge) << '\n';
			return 0;
    }
    
    make_union(x, y, parent, rank);
  }

  std::cout << 0 << '\n';
  return 0;
}