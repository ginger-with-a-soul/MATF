#include <iostream>
#include <vector>
#include <queue>


struct Graph {
	int size;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool> visited;
	std::vector<int> in_degrees;
	std::vector<int> topological_order;
	int edge_count;
	bool cycle_found;
	bool already_added;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.in_degrees.resize(n, 0);
	g.topological_order.resize(n, -1);
	g.edge_count = 0;
	g.cycle_found = false;
	g.already_added = false;
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.in_degrees[v] += 1;
	g.edge_count += 1;
}

void DFS(Graph &g, int u){
	if(g.cycle_found){
		return;
	}

	g.visited[u] = true;

	auto begin = g.ajd_list[u].begin();
	auto end = g.ajd_list[u].end();

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

void kahn(Graph &g){

	std::queue<int> nodes;

	for(int i = 0; i < g.size; i++){
		if(!g.in_degrees[i]){
			nodes.push(i);
		}
	}
	
	int tmp, top_order = 0;

	while(!nodes.empty()){
		tmp = nodes.front();
		nodes.pop();

		g.topological_order[tmp] = top_order;
		top_order += 1;

		auto begin = g.ajd_list[tmp].begin();
		auto end = g.ajd_list[tmp].end();

		while(begin != end){
			g.in_degrees[*begin] -= 1;
			if(!g.in_degrees[*begin]){
				nodes.push(*begin);
			}
			begin++;
		}
	}
}

void add_max_edges(Graph &g){
	for(int i = 0; i < g.size; i++){
		for(int j = i + 1; j < g.size; j++){
			std::cout << i << " " << j << std::endl;
			g.already_added = false;
			if(g.topological_order[i] < g.topological_order[j]){
				for(auto x : g.ajd_list[i]){
					std::cout << x << " ";
					if(x == j){
						g.already_added = true;
					}
				}
				if(!g.already_added){
					add_edge(g, i, j);
				}
			}
		}
	}
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 6);

	add_edge(g, 2, 3);
	add_edge(g, 3, 1);
	add_edge(g, 4, 1);
	add_edge(g, 4, 0);
	add_edge(g, 5, 0);
	add_edge(g, 5, 2);

	DFS(g, 5);
	if(g.cycle_found){
		std::cout << "Provided graph had a cycle to begin with!" << std::endl;
		exit(EXIT_SUCCESS);
	}
	g.visited.clear();
	g.visited.resize(g.size, false);

	kahn(g);
	add_max_edges(g);

	DFS(g, 5);
	if(g.cycle_found){
		std::cout << "Adding edges unsuccessful! Cycle found.." << std::endl;
		exit(EXIT_SUCCESS);
	}
	else{
		std::cout << "Adding edges successful! Max edged: " << g.edge_count << std::endl;
	}


	exit(EXIT_SUCCESS);
}