#include <iostream>
#include <vector>
#include <set>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	std::set<int> articulation_points;
	std::vector<int> parents;
	std::vector<int> times;
	std::vector<int> lower_times;
	int time;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.parents.resize(n, -1);
	g.time = 0;
	g.times.reserve(n);
	g.lower_times.reserve(n);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
}

void DFS(Graph &g, int u){
	g.visited[u] = true;
	g.times[u] = g.lower_times[u] = g.time;
	g.time += 1;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	int children = 0;

	while(begin != end){

		if(!g.visited[*begin]){
			g.parents[*begin] = u;
			DFS(g, *begin);

			children += 1;

			g.lower_times[u] = std::min(g.lower_times[u], g.lower_times[*begin]);

			if(g.parents[u] == -1 && children > 1){
				g.articulation_points.insert(u);
			}

			if(g.parents[u] != -1 && g.times[u] <= g.lower_times[*begin]){
				g.articulation_points.insert(u);
			}
		}
		else if(*begin != g.parents[u]){
			g.lower_times[u] = std::min(g.lower_times[u], g.lower_times[*begin]);
		}

		begin++;
	}
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 8);

	add_edge(g, 3, 2);
	add_edge(g, 3, 4);
	add_edge(g, 2, 0);
	add_edge(g, 2, 1);
	add_edge(g, 0, 1);
	add_edge(g, 4, 6);
	add_edge(g, 4, 5);
	add_edge(g, 5, 6);
	add_edge(g, 5, 7);

	DFS(g, 3);

	for(int i = 0; i < g.size; i++){
		if(g.articulation_points.find(i) == g.articulation_points.end()){
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;


	exit(EXIT_SUCCESS);
}