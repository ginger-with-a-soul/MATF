#include <iostream>
#include <vector>
#include <queue>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
}

void BFS(Graph &g, int u){
	g.visited[u] = true;

	std::queue<int> nodes;
	nodes.push(u);

	int tmp;

	while(!nodes.empty()){
		tmp = nodes.front();
		nodes.pop();

		std::cout << tmp << " ";

		auto begin = g.adj_list[tmp].begin();
		auto end = g.adj_list[tmp].end();

		while(begin != end){
			if(!g.visited[*begin]){
				g.visited[*begin] = true;
				nodes.push(*begin);
			}
			begin++;
		}
	}
	std::cout << std::endl;

}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 11);

	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 1, 7);
	add_edge(g, 1, 4);
	add_edge(g, 2, 5);
	add_edge(g, 2, 6);
	add_edge(g, 7, 3);
	add_edge(g, 7, 8);
	add_edge(g, 5, 9);
	add_edge(g, 6, 10);

	BFS(g, 0);

	exit(EXIT_SUCCESS);
}