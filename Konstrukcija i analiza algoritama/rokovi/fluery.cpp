#include <iostream>
#include <vector>
#include <algorithm>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	std::vector<int> degrees;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.degrees.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
	g.degrees[u]++; g.degrees[v]++;
}

void remove_edge(Graph &g, int u, int v){
	g.adj_list[u].erase(std::find(g.adj_list[u].begin(), g.adj_list[u].end(), v));
	g.adj_list[v].erase(std::find(g.adj_list[v].begin(), g.adj_list[v].end(), u));
}

void DFS(Graph &g, int u){
	g.visited[u] = true;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin);
		}
		begin++;
	}
}

bool valid_edge(Graph &g, int u, int v){
	if(g.adj_list[u].size() == 1){
		return true;
	}

	remove_edge(g, u, v);
	g.visited.resize(g.size, false);
	DFS(g, u);
	add_edge(g, u, v);
	if(!g.visited[v]){
		return false;
	}
	else{
		return true;
	}
}

void print_eulerian(Graph &g, int u){
	for(auto x : g.adj_list[u]){
		if(valid_edge(g, u, x)){
			std::cout << u << " --> " << x;
			std::cout << std::endl;
			remove_edge(g, u, x);
			print_eulerian(g, x);
			break;
		}
	}
}

void fleury(Graph &g){
	int odd = std::count_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x % 2;});
	int start;

	if(odd == 0){
		start = *std::find_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x > 0;});
		print_eulerian(g, start);
	}
	else if(odd == 2){
		start = *std::find_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x % 2;});
		print_eulerian(g, start);
	}
	else{
		std::cout << "Not Eulerian" << std::endl;
	}
}

int main(int argc, char** argv){

	Graph g;

	init_graph(g, 4);

  	// Put
  	add_edge(g, 0, 1);
  	add_edge(g, 0, 2);
  	add_edge(g, 1, 2);
  	add_edge(g, 2, 3);

	fleury(g);

	exit(EXIT_SUCCESS);
}