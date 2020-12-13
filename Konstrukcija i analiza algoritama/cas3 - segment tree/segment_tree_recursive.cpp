#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

void build_tree_rec(std::vector<int> &old, std::vector<int> &tree, int k, int x, int y){
	
	if(x == y){
		tree[k] = old[x];
		return;
	}

	int middle = (x + y) / 2;

	build_tree_rec(old, tree, 2 * k + 1, x, middle);
	build_tree_rec(old, tree, 2 * k + 2, middle + 1, y);

	tree[k] = tree[2 * k + 1] + tree[2 * k + 2];

}

int main(int argc, char** argv){

	std::vector<int> x = {1, 2, 3, 4, 5, 6, 7, 8};
	int height = ceil(log2(x.size()));
	int size = 2 * pow(2, height);

	std::vector<int> y(size);

	build_tree_rec(x, y, 0, 0, x.size() - 1);

	for(auto z : y){
		std::cout << z << " ";
	}
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}