/* 
Ojlerov put - krene iz nekog cvora, prodje kroz SVE grane grafa TACNO jednom i
zavrsi u nekom drugom cvoru
Ojlerov ciklus - krene iz nekog cvora, prodje kroz SVE grane grafa TACNO jednom i
zavrsi u cvoru iz kog je krenuo

Ojlerov put postoji akko imamo TACNO 2 cvora neparnog stepena (Ojlerov ciklus akko su
svu cvorovi parnog stepena) i ako svi cvorovi pripadaju toj komponenti povezanosti 
(ne razmatramo izolovane cvorove jer nas interesuju samo grane).

Ojlerov put krece iz jednog cvora neparnog stepena i zavrsava se u drugom cvoru neparnog
stepena. Ojlerov ciklus moze da krene iz bilo kog cvora.
Ojlerov ciklus mora da ima sve cvorove parnog stepena jer koliko puta moram da izadjem iz
nekog cvora, toliko puta moram da se vratim u njega. Kog Ojlerovog puta, iz neparnog stepena
krecem jer iz njega mogu da izadjem 1 put vise nego sto mogu da udjem, a zavrsavam u drugom
cvoru neparnog stepena jer u njega mogu da udjem jedan put vise nego sto mogu da izadjem.

Ojlerov algoritam:
	-prvo vidimo stepene svih cvorova, ako postoji vise od 2 sa neparnim onda nema ni puta ni
	ciklusa
	-zatim nadjemo neki cvor kome je stepen veci od 0 i uradimo dfs iz njega
	-zatim proverimo da li postoji neki cvor cije je stepen veci od 0 a da nije posecen
	-ako takav cvor postoji, nema ni puta ni ciklusa
	-ako ne postoji, onda postoji put ako je tacno 2 neparna cvora ili ciklus ako nema neparnih
*/


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

	g.degrees[u] += 1;
	g.degrees[v] += 1;
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

int num_of_odd(Graph &g){
	return std::count_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x % 2;});
}

int find_starting_node(Graph &g){
	auto x = std::find_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x > 0;});
	return *x;
}

int euler(Graph &g){
	int tmp = num_of_odd(g);

	if(tmp > 2){
		return 0;
	}

	int x = find_starting_node(g);

	DFS(g, x);

	for(int i = 0; i < g.size; i++){
		if(g.degrees[i] && !g.visited[i]){
			return 0;
		}
	}

	return tmp == 0? 2 : 1;
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 5);

	// Ciklus
  	//add_edge(g, 0, 1);
  	//add_edge(g, 1, 2);
  	//add_edge(g, 2, 0);

  	//Nije Ojlerov
  	add_edge(g, 0, 1);
  	add_edge(g, 1, 2);
  	add_edge(g, 1, 4);
  	add_edge(g, 2, 3);

  	// Put
  	add_edge(g, 0, 1);
  	add_edge(g, 0, 2);
  	add_edge(g, 0, 3);
  	add_edge(g, 1, 2);
  	add_edge(g, 1, 3);
  	add_edge(g, 2, 3);
  	add_edge(g, 2, 4);
  	add_edge(g, 3, 4);

	int res = euler(g);

	if(!res){
		std::cout << "Graph not Eulerian!" << std::endl;
	}
	else if(res == 1){
		std::cout << "Graph has Eulerian path!" << std::endl;
	}
	else{
		std::cout << "Graph has Eulerian cycle!" << std::endl;
	}

	exit(EXIT_SUCCESS);
}