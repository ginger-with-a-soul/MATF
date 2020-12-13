#include <iostream>
#include <vector>

struct Graph {
	int nodes;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	std::vector<int> path;
};

void init_graph(Graph &g, int n){
	g.nodes = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
}

void DFS(Graph &g, int u, int v){
	if(u == v){
		for(auto x : g.path){
			std::cout << x << " -> ";
		}
		
		std::cout << v << std::endl;
		return;
	}
	g.visited[u] = true;
	g.path.push_back(u);

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin, v);
		}

		begin++;
	}
	g.path.pop_back();
	g.visited[u] = false;
}

int main(int argc, char** argv){

	int n = 8, u, v;
	std::cin >> u >> v;
	Graph g;
	init_graph(g, n);

	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 2, 0);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 3, 4);
	add_edge(g, 4, 4);
	add_edge(g, 4, 2);

	add_edge(g, 5, 5);

	add_edge(g, 6, 7);
	add_edge(g, 1, 7);
	add_edge(g, 6, 0);

	DFS(g, u, v);

	exit(EXIT_SUCCESS);
}