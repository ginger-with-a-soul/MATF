#include <iostream>
#include <vector>
#include <set>

/* for a node to be an articulation point, that node has to be root and
have at least 2 children, or not to be a root and have its time be <= 
compared to lower_times of all its neighbours*/

struct  Graph {
	int size;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool> visited;
	std::vector<int> times;
	std::vector<int> lower_times;
	std::vector<int> parents;
	int time;
	std::set<int> articulation_points;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.parents.resize(n, -1);
	g.times.resize(n);
	g.lower_times.resize(n);
	g.time = 0;
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.ajd_list[v].push_back(u);
}

void DFS(Graph &g, int u){

	g.visited[u] = true;
	g.times[u] = g.lower_times[u] = g.time;
	g.time += 1;

	auto begin = g.ajd_list[u].begin();
	auto end = g.ajd_list[u].end();
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
			g.lower_times[u] = std::min(g.lower_times[u], g.times[*begin]);
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

	DFS(g, 0);

	for(auto x : g.articulation_points){
		std::cout << x << " "; 
	}
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}