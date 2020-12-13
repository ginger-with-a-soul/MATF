#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void build_seg_tree(std::vector<int> &array, std::vector<int> &seg_tree, int n){
	std::copy_n(array.begin(), n, seg_tree.begin() + n - 1);

	for(int k = n - 2; k >= 0; k--){
		seg_tree[k] = std::max(seg_tree[2 * k + 1], seg_tree[2 * k + 2]);
	}
}

int find_max(std::vector<int> &seg_tree, int k, int x, int y, int a, int b){
	if(x > b || y < a){
		return 0;
	}

	if(x >= a && y <= b){
		return seg_tree[k];
	}

	int middle = (x + y) / 2;

	return std::max(find_max(seg_tree, 2 * k + 1, x, middle, a, b),
				    find_max(seg_tree, 2 * k + 2, middle + 1, y, a, b));
}

int main(int argc, char** argv){

	std::vector<int> array = {3, 4, 1, 2, 6, 5, 1, 4};
	int n = array.size();

	int height = ceil(log2(n));
	int size = 2 * pow(2, height) - 1;

	std::vector<int> seg_tree(size);
	build_seg_tree(array, seg_tree, n);

	int a, b;
	std::cin >> a >> b;

	std::cout << find_max(seg_tree, 0, 0, n - 1, a, b) << std::endl;
	

	exit(EXIT_SUCCESS);
}