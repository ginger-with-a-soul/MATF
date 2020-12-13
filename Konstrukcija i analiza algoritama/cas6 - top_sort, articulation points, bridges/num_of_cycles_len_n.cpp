#include <iostream>
#include <vector>
#include <algorithm>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	double num_of_cycles;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.num_of_cycles = 0;
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
}

void DFS(Graph &g, int u, int start, int n){
	
	g.visited[u] = true;
	if(n == 0){
		if(std::find(g.adj_list[u].begin(), g.adj_list[u].end(), start) != g.adj_list[u].end()){
			g.num_of_cycles += 0.5;
		}
		g.visited[u] = false;
		return;
	}

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){

		if(!g.visited[*begin]){
			DFS(g, *begin, start, n - 1);
		}

		begin++;
	}

	g.visited[u] = false;

}

int main(int argc, char** argv){

	int n;
	std::cin >> n;

	Graph g;
	init_graph(g, 7);

	add_edge(g, 0, 1);
	add_edge(g, 1, 2);
	add_edge(g, 2, 3);
	add_edge(g, 3, 0);
	add_edge(g, 3, 4);
	add_edge(g, 4, 5);
	add_edge(g, 5, 6);
	add_edge(g, 6, 3);

	for(int i = 0; i < g.size - (n - 1); i++){
		DFS(g, i, i, n - 1);
		g.visited[i] = true;
	}

	std::cout << g.num_of_cycles << std::endl;

	exit(EXIT_SUCCESS);
}