#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

struct Graph {
	int size;
	std::vector<std::vector<int>> ajd_list;
	std::vector<int> degrees;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.ajd_list.reserve(n);
	g.degrees.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.degrees[u]++;
	g.degrees[v]--;
}

vodi hierholzer(Graph &g, int u){
	std::stack<int> stack;
	std::stack<int> path;

	stack.push(u);
	int tmp;
	while(!stack.empty()){
		if(g.ajd_list[u].size()){
			stack.push(u);
			tmp = stack.top();

			u = g.ajd_list[u].back();
			g.ajd_list[tmp].pop_back();
		}
		else{
			path.push(u);
			u = stack.top();
			stack.pop();
		}
	}

	while(!path.empty()){
		std::cout << path.top() << " ";
		path.pop();
	}

	std::cout << std::endl;
}

int main(int argc, char** argv){

	Graph g;

  	init_graph(g, 5);

  	add_edge(g, 0, 1);
  	add_edge(g, 1, 2);
  	add_edge(g, 1, 3);
  	add_edge(g, 2, 0);
  	add_edge(g, 3, 4);
  	add_edge(g, 4, 1);

	//first kosaraju but let's assume it is eulerian

	int odd = std::count_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x % 2;});
	int start;

	if(odd == 0){
		start = *std::find_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x == 0;});
		hierholzer(g, start);
	}
	else if(odd == 2){
		start = *std::find_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x > 0;});
		hierholzer(g, start);
	}
	else{
		std::cout << "Not eulerian!" << std::endl;
	}

	exit(EXIT_SUCCESS);
}