#include <iostream>
#include <vector>
#include <queue>

struct Graph {
	int nodes;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool>visited;
};

void init_graph(Graph &g, int n){
	g.nodes = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
}

void BFS(Graph &g, int u){
	std::queue<int> nodes;
	g.visited[u] = true;
	nodes.push(u);

	int tmp;
	
	while(!nodes.empty()){

		tmp = nodes.front();
		nodes.pop();

		auto begin = g.ajd_list[tmp].begin();
		auto end = g.ajd_list[tmp].end();

		std::cout << tmp << " ";

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
	init_graph(g, 7);

	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 1, 6);
	add_edge(g, 2, 0);
	add_edge(g, 3, 4);
	add_edge(g, 4, 4);
	add_edge(g, 4, 2);
	add_edge(g, 5, 0);
	add_edge(g, 5, 6);
	
	BFS(g, 0);

	exit(EXIT_SUCCESS);
}