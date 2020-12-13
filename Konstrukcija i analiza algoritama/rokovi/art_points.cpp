#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	int time;
	std::vector<int> times;
	std::vector<int> lower_times;
	std::vector<int> parents;
	std::vector<bool> visited;
	std::set<int> art_points;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.lower_times.resize(n);
	g.time = 0;
	g.times.resize(n);
	g.visited.resize(n, false);
	g.parents.resize(n, -1);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
}

void DFS(Graph &g, int u){
	g.visited[u] = true;
	g.times[u] = g.lower_times[u] = g.time++;

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
				g.art_points.insert(u);
			}

			if(g.parents[u] != -1 && g.times[u] <= g.lower_times[*begin]){
				g.art_points.insert(u);
			}
		}
		else if(g.parents[u] != *begin){
			g.lower_times[u] = std::min(g.lower_times[u], g.times[*begin]);
		}
		begin++;
	}

}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 5);

	add_edge(g, 0, 1);
	add_edge(g, 0, 4);
	add_edge(g, 1, 2);
	add_edge(g, 2, 3);
	add_edge(g, 3, 1);

	DFS(g, 0);

	for(auto x : g.art_points){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}