#include <iostream>
#include <vector>
#include <queue>

//graph has to be directed acyclic - DAG

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<int> in_degree;
	std::vector<std::pair<int, int>> undirected_edges;
	std::vector<int> topological_order;
	std::vector<bool> visited;
	bool cycle_found = false;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.in_degree.resize(n, 0);
	g.topological_order.resize(n, -1);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.in_degree[v] += 1;
}

void add_undirected_edge(Graph &g, int u, int v){
	g.undirected_edges.push_back(std::make_pair(u, v));
}

void kahn(Graph &g){

	std::queue<int> nodes;
	int top_order = 0;

	for(int i = 0; i < g.size; i++){
		if(!g.in_degree[i]){
			nodes.push(i);
		}
	}

	int tmp;

	while(!nodes.empty()){
		tmp = nodes.front();
		nodes.pop();

		g.topological_order[tmp] = top_order;
		top_order += 1;

		for(auto x : g.adj_list[tmp]){
			g.in_degree[x] -= 1;
			if(!g.in_degree[x]){
				nodes.push(x);
			}
		}
	}

}

void DFS(Graph &g, int u){

	if(g.cycle_found){
		return;
	}

	g.visited[u] = true;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(g.visited[*begin]){
			g.cycle_found = true;
			return;
		}
		else{
			DFS(g, *begin);
		}

		begin++;
	}
	g.visited[u] = false;


}

void direct_undirected_edges(Graph &g){

	for(auto x : g.undirected_edges){
		if(g.topological_order[x.first] < g.topological_order[x.second]){
			add_edge(g, x.first, x.second);
		}
		else{
			add_edge(g, x.second, x. first);
		}
	}

}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 6);

	add_edge(g, 0, 1);
	add_edge(g, 0, 5);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 1, 4);
	add_edge(g, 2, 3);
	add_edge(g, 5, 1);
	add_edge(g, 5, 2);

	add_undirected_edge(g, 0, 3);
	add_undirected_edge(g, 4, 5);
	add_undirected_edge(g, 0, 2);

	DFS(g, 0);

	if(g.cycle_found){
		std::cout << "Provided graph was cyclic to begin with!" << std::endl;
		exit(EXIT_SUCCESS);
	}
	else{
		g.visited.clear();
		g.visited.resize(g.size, false);
	}

	kahn(g);

	direct_undirected_edges(g);

	DFS(g, 0);
	if(g.cycle_found){
		std::cout << "There IS a cycle! Kahn's failure.." << std::endl;
	}
	else{
		std::cout << "There is NOT a cycle! Directing successful.." << std::endl;
	}

	exit(EXIT_SUCCESS);
}