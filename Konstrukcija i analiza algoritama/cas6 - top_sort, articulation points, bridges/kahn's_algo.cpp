#include <iostream>
#include <vector>
#include <queue>

//graph has to be directed acyclic - DAG

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<int> in_degree;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.in_degree.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.in_degree[v] += 1;
}

void kahn(Graph &g){

	std::queue<int> nodes;

	for(int i = 0; i < g.size; i++){
		if(!g.in_degree[i]){
			nodes.push(i);
		}
	}

	int tmp;

	while(!nodes.empty()){
		tmp = nodes.front();
		nodes.pop();
		std::cout << tmp << " ";

		for(auto x : g.adj_list[tmp]){
			g.in_degree[x] -= 1;
			if(!g.in_degree[x]){
				nodes.push(x);
			}
		}
	}

	std::cout << std::endl;
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 6);

	add_edge(g, 0, 1);
	add_edge(g, 1, 4);
	add_edge(g, 3, 0);
	add_edge(g, 3, 2);
	add_edge(g, 2, 4);
	add_edge(g, 5, 2);
	add_edge(g, 5, 4);

	kahn(g);

	exit(EXIT_SUCCESS);
}