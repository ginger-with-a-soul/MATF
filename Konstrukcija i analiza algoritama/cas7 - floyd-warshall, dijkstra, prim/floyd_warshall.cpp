/* flojd-varsalov algoritam nam omogucava da nadjemo nakrace puteve izmedju svaka
dva cvora.
Prvo alociramo kvadratnu matricu dimenzije broja cvorova. Zatim glavnu dijagonalu 
inicijalizujemo na 0 a sve ostalo na INF. Ako postoji ciklus negativne cene,
flojd-varsalov algoritam ne radi!
Zatim se krecemo preko svakog, od svakog, do svakog cvora. Ako je cena puta od cvora
do cvora manja od cene puta od cvora do preko cvora pa od preko cvora do cvora, onda
je azuriramo. Ako je nakon ovoga, neki element na dijagonali negativan, to znaci da 
postoji ciklus negativne duzine*/

#include <iostream>
#include <vector>

#define INF 99999

struct Graph {
	int **matrix;
	int size;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.matrix = (int**)malloc(n * sizeof(int*));
	for(int i = 0; i < n; i++){
		g.matrix[i] = (int*)malloc(n * sizeof(int));
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j){
				g.matrix[i][j] = 0;
			}
			else{
				g.matrix[i][j] = INF;
			}
		}
	}
}

void add_edge(Graph &g, int u, int v, int d){
	g.matrix[u][v] = d;
}

void floyd_warshall(Graph &g){
	for(int k = 0; k < g.size; k++){
		for(int i = 0; i < g.size; i++){
			for(int j = 0; j < g.size; j++){
				if(g.matrix[i][j] > g.matrix[i][k] + g.matrix[k][j]){
					g.matrix[i][j] = g.matrix[i][k] + g.matrix[k][j];
				}
			}
		}
	}

	for(int i = 0; i < g.size; i++){
		if(g.matrix[i][i] < 0){
			std::cout << "There IS a negative cycle!" << std::endl;
			return;
		}
	}
	std::cout << "There IS NOT a negative cycle!" << std::endl;
}


int main(int argc, char** argv){

	Graph g;
	init_graph(g, 4);

	add_edge(g, 0, 1, 1);
	add_edge(g, 1, 2, -1);
	add_edge(g, 2, 3, -1);
	add_edge(g, 3, 1, -1);

	floyd_warshall(g);

	exit(EXIT_SUCCESS);
}