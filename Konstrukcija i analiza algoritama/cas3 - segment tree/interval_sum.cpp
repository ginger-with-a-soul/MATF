#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void build_tree_iter(std::vector<int> &oldA, std::vector<int> &newA1, int n){

	std::copy_n(oldA.begin(), n, newA1.begin() + n - 1);

	for(int k = n - 2; k >= 0; k--){
		newA1[k] = newA1[2 * k + 1] + newA1[2 * k + 2];
	}

}

void build_tree_rec(std::vector<int> &oldA, std::vector<int> &newA2, int k, int x, int y){
	if(x == y){
		newA2[k] = oldA[x];
		return;
	}

	int middle = (x + y) / 2;

	build_tree_rec(oldA, newA2, 2 * k + 1, x, middle);
	build_tree_rec(oldA, newA2, 2 * k + 2, middle + 1, y);

	newA2[k] = newA2[2 * k + 1] + newA2[2 * k + 2];

}

int get_sum(std::vector<int> &seg_tree, int k, int x, int y, int a, int b){
	
	if(x > b || y < a){
		return 0;
	}

	if(x >= a && y <= b){
		return seg_tree[k];
	}

	int middle = (x + y) / 2;

	return get_sum(seg_tree, 2 * k + 1, x, middle, a, b) + get_sum(seg_tree, 2 * k + 2, middle + 1, y, a, b);
}

int main(int argc, char** argv){

	std::vector<int> oldA = {3, 4, 1, 2, 6, 5, 1, 4};
	int oaSize = oldA.size();

	int height = ceil(log2(oaSize));
	int size = 2 * pow(2, height) - 1;
	std::vector<int> newA1(size);
	std::vector<int> newA2(size);

	build_tree_iter(oldA, newA1, oaSize);
	build_tree_rec(oldA, newA2, 0, 0, oaSize - 1);
	
	std::cout << "Input interval from 0 to " << oaSize - 1 << std::endl;
	int a, b;
	std::cin >> a >> b;

	std::cout << "Sum is: " << get_sum(newA2, 0, 0, oaSize - 1, a, b) << std::endl;

	exit(EXIT_SUCCESS);
}