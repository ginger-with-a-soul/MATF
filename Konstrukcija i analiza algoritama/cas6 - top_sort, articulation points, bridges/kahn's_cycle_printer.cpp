#include <iostream>
#include <vector>
#include <queue>

struct Graph {
	int size;
	std::vector<std::vector<int>> ajd_list;
	std::vector<int> in_degree;
	std::vector<int> cycle;
	int flag = 0;
	std::vector<bool> visited;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.ajd_list.reserve(n);
	g.in_degree.resize(n, 0);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.in_degree[v] += 1;
}

void kahn(Graph &g){
	std::queue<int> nodes;

	for(int i = 0; i < g.size; i++){
		if(!g.in_degree[i]){
			nodes.push(i);
			g.flag += 1;
		}
	}

	int tmp;

	while(!nodes.empty()){
		tmp = nodes.front();
		nodes.pop();
		g.cycle.push_back(tmp);

		for(int x : g.ajd_list[tmp]){
			g.in_degree[x] -= 1;
			if(!g.in_degree[x]){
				nodes.push(x);
				g.flag += 1;
			}
		}
	}
}

void DFS(Graph &g, int u){
	g.visited[u] = true;

	g.cycle.push_back(u);

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

	Graph g;
	
	//init_graph(g, 5)

	//add_edge(g, 0, 1);
	//add_edge(g, 1, 2);
	//add_edge(g, 2, 3);
	//add_edge(g, 3, 4);
	//add_edge(g, 4, 1);
	//add_edge(g, 4, 2);

	init_graph(g, 6);

	add_edge(g, 0, 1);
	add_edge(g, 1, 4);
	add_edge(g, 3, 0);
	add_edge(g, 3, 2);
	add_edge(g, 2, 4);
	add_edge(g, 5, 2);
	add_edge(g, 5, 4);

	kahn(g);

	if(g.flag == g.size){
		std::cout << "Topological: ";
		for(auto x : g.cycle){
			std::cout << x << " ";
		}
		std::cout << std::endl;
	}
	else{
		g.cycle.clear();
		for(int i = 0; i < g.size; i++){
			if(g.in_degree[i]){
				DFS(g, i);
				break;
			}
		}
		std::cout << "Cycle: ";
		for(auto x : g.cycle){
			std::cout << x << " ";
		}
		std::cout << std::endl;
	}

	exit(EXIT_SUCCESS);
}