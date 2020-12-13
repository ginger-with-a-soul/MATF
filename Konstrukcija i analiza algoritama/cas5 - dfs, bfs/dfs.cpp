#include <iostream>
#include <vector>

struct Graph {
	int node_num;
	std::vector<bool> visited;
	std::vector<std::vector<int>> adj_list;
};

void init_graph(Graph &g, int n){
	g.node_num = n;
	g.visited.resize(n, false);
	g.adj_list.reserve(n);
}

void add_edge(Graph &g, int x, int y){
	g.adj_list[x].push_back(y);
}

void DFS(Graph &g, int x){
	g.visited[x] = true;
	std::cout << x << " ";

	auto begin = g.adj_list[x].begin();
	auto end = g.adj_list[x].end();

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
	add_edge(g, 1, 2);
	add_edge(g, 0, 2);
	add_edge(g, 2, 0);
	add_edge(g, 2, 3);
	add_edge(g, 3, 3);

	DFS(g, 0);
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}