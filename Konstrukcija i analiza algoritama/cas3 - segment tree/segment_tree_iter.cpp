#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void build_segment_tree(std::vector<int> &old, std::vector<int> &new1, int n){

	std::copy_n(old.begin(), n, new1.begin() + n);

	for(int k = n - 1; k > 0; k--){
		new1[k] = new1[2 * k] + new1[2 * k + 1];
	}
}

int main(int argc, char** argv){

	std::vector<int> x = {1, 2, 3, 4, 5, 6, 7, 8};
	
	int height = ceil(log2(x.size()));
	int size = 2 * pow(2, height);
	std::vector<int> y(size);

	build_segment_tree(x, y, x.size());

	for(auto x : y){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}