#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

int find(std::vector<int> &parents, int x){
	while(x != parents[x]){
		x = parents[x];
	}

	return x;
}

void unionV2(std::vector<int> &parents, std::vector<int> &rang, int x, int y){
	int px = find(parents, x);
	int py = find(parents, y);

	if(rang[px] < rang[py]){
		parents[px] = py;
	}
	else if(rang[px] > rang[py]){
		parents[py] = px;
	}
	else{
		parents[py] = px;
		rang[px]++;
	}
}

bool compare(std::tuple<int, int, int> x, std::tuple<int, int, int> y){
	return std::get<0>(x) > std::get<0>(y);
}

int main(){

	int n, m;
	std::cin >> n >> m;
	std::vector<int> parents(n), rang(n);

	for(int i = 0; i < n; i++){
		parents[i] = i;
	}

	std::vector<std::tuple<int, int, int>> edges(m);
	for(int i = 0; i < m; i++){
		std::cin >> std::get<0>(edges[i]) >> std::get<1>(edges[i]) >> std::get<2>(edges[i]);
	}

	std::sort(edges.begin(), edges.end(), compare);

	for(auto edge : edges){
		int x = std::get<1>(edge);
		int y = std::get<2>(edge);

		if(find(parents, x) == find(parents, y)){
			std::cout << std::get<0>(edge) << std::endl;
		}

		unionV2(parents, rang, x, y);
	}

	exit(EXIT_SUCCESS);
}