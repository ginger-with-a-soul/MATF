#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <set>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	std::vector<int> parents;
	std::vector<int> times;
	std::vector<int> lower_times;
	std::set<int> result;
	int time;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.parents.resize(n, -1);
	g.times.resize(n, INT_MAX);
	g.lower_times.resize(n, INT_MAX);
	g.visited.resize(n, false);
	g.time = 0;
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
}

void articulation_points(Graph &g, int u){

	g.lower_times[u] = g.times[u] = g.time;
	g.time++;
	g.visited[u] = true;

	int children = 0;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(!g.visited[*begin]){
			g.parents[*begin] = u;
			articulation_points(g, *begin);

			children += 1;
			g.lower_times[u] = std::min(g.lower_times[u], g.lower_times[*begin]);

			if(g.parents[u] == -1 && children > 1){
				g.result.insert(u);
			}

			if(g.parents[u] != -1 && g.times[u] <= g.lower_times[*begin]){
				g.result.insert(u);
			}
		}
		else if(g.parents[u] != *begin){
			g.lower_times[u] = std::min(g.lower_times[u], g.times[*begin]);
		}
		begin++;
	}

}

int main(int argc, char** argv){

	int n, k, u, v;
	std::cin >> n >> k;
	Graph g;
	init_graph(g, n);

	for(int i = 0; i < k; i++){
		std::cin >> u >> v;
		add_edge(g, u, v);
	}

	articulation_points(g, 0);

	for(auto x : g.result){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}