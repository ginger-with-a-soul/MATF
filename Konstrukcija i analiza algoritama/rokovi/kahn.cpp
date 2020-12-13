#include <iostream>
#include <vector>
#include <queue>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::queue<int> zero_degrees;
	std::vector<int> in_degrees;
	int collected;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.collected = 0;
	g.in_degrees.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.in_degrees[v] += 1;
}

void kahn(Graph &g){
	for(int i = 0; i < g.size; i++){
		if(!g.in_degrees[i]){
			g.zero_degrees.push(i);
		}
	}
	std::vector<int> top_sort;

	while(!g.zero_degrees.empty()){
		int tmp = g.zero_degrees.front();
		g.zero_degrees.pop();
		g.collected += 1;
		top_sort.push_back(tmp);

		for(auto x : g.adj_list[tmp]){
			g.in_degrees[x] -= 1;
			if(!g.in_degrees[x]){
				g.zero_degrees.push(x);
			}
		}
	}

	if(g.collected == g.size){
		for(auto x : top_sort){
			std::cout << x << " ";
		}
		std::cout << std::endl;
	}
	else{
		std::cout << "Graph has a cycle!" << std::endl;
	}
}

int main(int argc, char** argv){


	Graph g;
	init_graph(g, 6);

	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 1, 2);
	add_edge(g, 1, 4);
	add_edge(g, 2, 3);
	add_edge(g, 3, 4);
	add_edge(g, 4, 5);

	kahn(g);

	exit(EXIT_SUCCESS);
}