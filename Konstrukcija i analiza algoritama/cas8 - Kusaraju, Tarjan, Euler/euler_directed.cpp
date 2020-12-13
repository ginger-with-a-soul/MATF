/*
Usmereni graf sadrzi Ojlerov ciklus akko je graf (bez razmatranja izolovanih cvorova)
jako povezan i ulazni stepen svakog cvora je jednak njegovom izlaznom stepenu.
U usmerenog grafu postoji Ojlerov put akko je graf jako povezan i postoje dva cvora gde je
stepen neparan (jedan cvor ima vise izlaznih -> od njega krecemo, nego ulaznih grana, a drugi
cvor ima vise ulaznih -> tu zavrsavamo, nego izlaznih grana).
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<std::vector<int>> reverse_adj_list;
	std::vector<bool> visited;
	std::vector<int> degrees;
	std::vector<bool> degrees_change;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.degrees.resize(n, 0);
	g.reverse_adj_list.reserve(n);
	g.degrees_change.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.reverse_adj_list[v].push_back(u);
	g.degrees_change[u] = true;
	g.degrees_change[v] = true;
	g.degrees[u] += 1;
	g.degrees[v] -= 1;
}

int find_starting_node(Graph &g){
	return *std::find_if(g.degrees_change.begin(), g.degrees_change.end(), [](const bool x){return x;});
}


void DFS(Graph &g, int u, int initiated){
	g.visited[u] = true;

	std::vector<int>::iterator begin, end;

	if(!initiated){
		begin = g.adj_list[u].begin();
		end = g.adj_list[u].end();
	}
	else{
		begin = g.reverse_adj_list[u].begin();
		end = g.reverse_adj_list[u].end();
	}

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin, initiated);
		}

		begin++;
	}
}

bool kosaraju(Graph &g, int u){
	int initiated = 0;
	DFS(g, u, initiated);
	if(std::find_if(g.visited.begin(), g.visited.end(), [](const bool x){return !x;}) != g.visited.end()){
		return false;
	}
	else{
		g.visited.clear();
		g.visited.resize(g.size, false);
		DFS(g, u, initiated + 1);
		if(std::find_if(g.visited.begin(), g.visited.end(), [](const bool x){return !x;}) != g.visited.end()){
			return false;
		}
	}
	return true;
}

int euler(Graph &g){
	int start = find_starting_node(g);
	std::cout << start << std::endl;
	if(!kosaraju(g, start)){
		return 0;
	}
	
	int in = 0, out = 0, equal = 0;
	for(int i = 0; i < g.size; i++){
		if(g.degrees[i] < 0){
			std::cout << i << " ";
			in++;
		}
		else if(g.degrees[i] > 0){
			std::cout << i << " ";
			out++;
		}
		else{
			equal++;
		}
	}

	if(equal == g.size){
		return 2;
	}
	else if(out + in == 2){
		return 1;
	}
	else{
		return 0;
	}
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 5);

  	 // Euler's cycle
  	add_edge(g, 0, 2);
  	add_edge(g, 0, 3);
  	add_edge(g, 1, 0);
  	add_edge(g, 2, 1);
  	add_edge(g, 3, 4);
  	add_edge(g, 4, 0);
  	

	int res = euler(g);

	std::cout << (res == 0? "Not Eulerian!" : (res == 1? "Eulerian path!" : "Eulerian cycle")) << std::endl;

	exit(EXIT_SUCCESS);
}