#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <numeric>

/* primov algoritam sluzi za odredjivanje minimalnog razapinjuceg stabla.
Na pocetku krenemo od nekog cvora, kazemo da smo ga posetili i ne racunamo ga
u ukupnu cenu jer je pocetni cvor. Ako imamo n cvorova onda cemo imati n - 1
grana pa toliko puta treba vrteti petlju. Zatim od svih cvorova nadjemo onaj koji 
nismo posetili vec a ima minimalnu cenu (na pocetku je to uvek cvor od kojeg krecemo
jer svi ostali ima INF vrednost). Kazemo da smo ga posetili i onda prodjemo
kroz sve njegove susede i azuriramo im cenu ako je to potrebno i oznacimo ko ima je
roditelj.
*/

struct Graph {
	int size;
	std::vector<std::vector<std::pair<int, int>>> ajd_list;
	std::vector<bool> visited;
	std::vector<int> parents;
	int result;
	std::vector<int> egde_cost_for_node;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.parents.resize(n, -1);
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.result = 0;
	g.egde_cost_for_node.resize(n, INT_MAX);
}

void add_edge(Graph &g, int u, int v, int d){
	g.ajd_list[u].push_back(std::make_pair(v, d));
	g.ajd_list[v].push_back(std::make_pair(u, d));
}

int find_min_not_visited(Graph &g){
	int min_cost = INT_MAX;
	int min_index = -1;

	for(int i = 0; i < g.size; i++){
		if(!g.visited[i] && g.egde_cost_for_node[i] < min_cost){
			min_cost = g.egde_cost_for_node[i];
			min_index = i;
		}
	}

	return min_index;
}

void prims(Graph &g, int u){

	g.egde_cost_for_node[u] = 0;

	for(int i = 0; i < g.size - 1; i++){
		int tmp = find_min_not_visited(g);

		g.visited[tmp] = true;

		auto begin = g.ajd_list[tmp].begin();
		auto end = g.ajd_list[tmp].end();

		while(begin != end){
			if(!g.visited[(*begin).first] && (*begin).second < g.egde_cost_for_node[(*begin).first]){
				g.egde_cost_for_node[(*begin).first] = (*begin).second;
				g.parents[(*begin).first] = tmp;
			}
			begin++;
		}
	}

	std::cout << std::accumulate(g.egde_cost_for_node.begin(), g.egde_cost_for_node.end(), 0,
																[](const int x, const int y){
																	return x + y;
																}) << std::endl;

}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 5);

	add_edge(g, 0, 1, 1);
	add_edge(g, 0, 2, 5);
	add_edge(g, 0, 3, 10);
	add_edge(g, 0, 4, 4);
	add_edge(g, 4, 1, 1);
	add_edge(g, 1, 2, 2);
	add_edge(g, 2, 3, 4);

	prims(g, 0);

	exit(EXIT_SUCCESS);
}