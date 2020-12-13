#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>

struct Graph {
	int size;
	std::vector<std::vector<std::pair<int, int>>> adj_list;
	std::vector<bool> visited;
	std::vector<int> edges_cost;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.edges_cost.resize(n, INT_MAX);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v, int d){
	g.adj_list[u].push_back(std::make_pair(v, d));
	g.adj_list[v].push_back(std::make_pair(u, d));
}

int find_min(Graph &g){
	int min = INT_MAX;
	int index = -1;

	for(int i = 0; i < g.size; i++){
		if(!g.visited[i] && g.edges_cost[i] < min){
			min = g.edges_cost[i];
			index = i;
		}
	}

	return index;
}

int prims(Graph &g, int u){
	g.edges_cost[u] = 0;
	int tmp;

	for(int i = 0; i < g.size - 1; i++){
		tmp = find_min(g);
		g.visited[tmp] = true;

		auto begin = g.adj_list[tmp].begin();
		auto end = g.adj_list[tmp].end();

		while(begin != end){
			if(!g.visited[(*begin).first] && (*begin).second < g.edges_cost[(*begin).first]){
				g.edges_cost[(*begin).first] = (*begin).second;
			}

			begin++;
		}
	}

	return std::accumulate(g.edges_cost.begin(), g.edges_cost.end(), 0, [](const int x, const int y)
																		{
																			return x + y;
																		});
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

	std::cout << prims(g, 0) << std::endl;

	exit(EXIT_SUCCESS);
}