/* u neusmerenom grafu imamo dve vrste grana - grana grafa i povratna grana
(grana koja vodi po vec posecenog cvora koji nije roditelj - formira ciklus). 
U usmerenom postoji 4 vrste grana - direktne (vode do potomaka koji nisu direktni
potomci), poprecne, povratne.
Graf je jako povezan ako za svaka dva cvora u usmerenom grafu mozemo da nadjemo
put izmedju njih. Ko neusmerenih grafova, ako imamo jednu komponentu povezanosti,
onda je graf sigurno jako povezan jer iz svakog cvora postoji put do svakog cvora.
Podgraf jako povezanog grafa je komponenta jake povezanosti grafa. Komponente jake
povezanost su povezane ciklusom. Pronalaskom svih ciklusa u grafu, nalazimo i
komponente jake povezanosti.

Tarjanov algoritam za odredjivanje komp. jake povezanosti:
-krenemo od nekog cvora (nije vazno kog), stavimo mu odmah ulazno vreme i lower_time
i dodamo ga na stek i zabelezimo u vektoru da je taj element na steku.
-zatim prolazimo kroz sve susede tog cvora:
	Ako nisu poseceni, pokrecemo dfs iz njih.
Kada izadjemo iz tog rekurzivnog poziva, gledamo da li treba da azuriramo lower_time
trenutnog cvora tako da bude min od lower_time njegovih suseda.
	Ako jesu poseceni, i na steku su (to znaci da pripadaju istoj komponenti povezanosti)
onda azuriramo lower_time trenutnog cvora da bude min od lower_time njega i time-a njegovih
suseda. Svi cvorovi koji pripadaju istoj komp. jake povezanosti imaju isti lower_time.
Lower_time nam govori koji je to najraniji cvor (gledamo ulaznu numeraciju) sa kojim trenutni
moze da formira ciklus
-kada obidjemo sve cvorove, gledamo da li je trenutni cvor u kom smo bas koreni cvor trenutne
komponente jake povezanost (ako su mu time i lower_time jednaki). Ako jeste, onda skidamo
elemente sa steka sve dok ne dodjemo do naseg korenog cvora (ti elementi pripadaju komponenti
jake povezanosti).*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::stack<int> stack;
	std::vector<bool> in_stack;
	std::vector<int> times;
	std::vector<int> lower_times;
	int time;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.in_stack.resize(n, false);
	g.times.resize(n, -1);
	g.lower_times.resize(n, -1);
	g.time = 0;
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
}

void DFS(Graph &g, int u){
	g.times[u] = g.lower_times[u] = g.time;
	g.time += 1;
	g.stack.push(u);
	g.in_stack[u] = true;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(g.times[*begin] == -1){
			DFS(g, *begin);

			g.lower_times[u] = std::min(g.lower_times[u], g.lower_times[*begin]);
		}
		else if(g.in_stack[*begin]){
			g.lower_times[u] = std::min(g.lower_times[u], g.times[*begin]);
		}

		begin++;
	}

	int tmp;
	if(g.times[u] == g.lower_times[u]){
		while(1){
			tmp = g.stack.top();
			g.stack.pop();
			g.in_stack[tmp] = false;

			std::cout << tmp << " ";

			if(tmp == u){
				std::cout << std::endl;
				break;
			}
		}
	}

}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 8);

	add_edge(g, 0, 1);
  	add_edge(g, 0, 2);
  	add_edge(g, 1, 0);
  	add_edge(g, 1, 3);
  	add_edge(g, 2, 3);
  	add_edge(g, 3, 4);
  	add_edge(g, 3, 5);
  	add_edge(g, 4, 2);
  	add_edge(g, 4, 5);
  	add_edge(g, 4, 6);
  	add_edge(g, 5, 7);
  	add_edge(g, 6, 5);
  	add_edge(g, 7, 6);

	DFS(g, 0);

	exit(EXIT_SUCCESS);
}