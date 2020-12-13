#include <iostream>
#include <vector>

struct Graph {
	int nodes;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool> visited;
	int compNum = 0;
};

void init_graph(Graph &g, int n){
	g.nodes = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.ajd_list[v].push_back(u);
}

void DFS(Graph &g, int u){
	g.visited[u] = true;

	auto begin = g.ajd_list[u].begin();
	auto end = g.ajd_list[u].end();

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin);
		}

		begin++;
	}
}

int main(int argc, char** argv){

	int n;
	std::cin >> n;

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
	//add_edge(g, 6, 5);
	//add_edge(g, 5, 3);

	for(int i = 0; i < n; i++){
		if(!g.visited[i]){
			g.compNum += 1;
		    DFS(g, i);
		}
	}

	std::cout << "Number of components: " << g.compNum << std::endl;

	exit(EXIT_SUCCESS);
}