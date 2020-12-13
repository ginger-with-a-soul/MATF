#include <iostream>
#include <vector>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	bool cycle_found;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.cycle_found = false;
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
}

void DFS(Graph &g, int u, int v){

	g.visited[u] = true;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){

		if(!g.visited[*begin]){
			DFS(g, *begin, v);
		}
		else{
			if(*begin == v){
				g.cycle_found = true;
				return;
			}
		}

		begin++;
	}

	if(g.cycle_found){
		return;
	}

	g.visited[u] = false;
}

int main(int argc, char** argv){

	Graph g;
	int n, m, u, v;
	std::cin >> n >> m;

	init_graph(g, n);

	for(int i = 0; i < m; i++){
		std::cin >> u >> v;
		add_edge(g, u, v);
	}

	DFS(g, 0, 0);
	bool all_visited = true;

	for(int i = 0; i < g.size; i++){
		if(!g.visited[i]){
			std::cout << i << std::endl;
			all_visited = false;
			break;
		}
	}

	if(g.cycle_found && all_visited){
		std::cout << "DA" << std::endl;
	}
	else{
		std::cout << "NE" << std::endl;
	}

	exit(EXIT_SUCCESS);
}