#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void build_tree(std::vector<int> &array, std::vector<int> &seg_tree, int k, int x, int y){
	if(x == y){
		seg_tree[k] = array[x];
		return;
	}

	int middle = (x + y) / 2;

	build_tree(array, seg_tree, k * 2 + 1, x, middle);
	build_tree(array, seg_tree, k * 2 + 2, middle + 1, y);

	seg_tree[k] = seg_tree[2 * k + 1] + seg_tree[2 * k + 2];
}

void update_tree(std::vector<int> &seg_tree, int k, int x, int y, int index, int value){
	if(x == y){
		seg_tree[k] = value;
		return;
	}

	int middle = (x + y) / 2;

	if(index <= middle){
		update_tree(seg_tree, k * 2 + 1, x, middle, index, value);
	}
	else{
		update_tree(seg_tree, k * 2 + 2, middle + 1, y, index, value);
	}

	seg_tree[k] = seg_tree[k * 2 + 1] + seg_tree[k * 2 + 2];
}

int main(int argc, char** argv){

	std::vector<int> array = {-1, 0, 2, -4, 3, 2, 5, 2};
	int n = array.size();
	int height = ceil(log(n));
	int size = 2 * pow(2, height) - 1;
	
	std::vector<int> seg_tree(size);

	build_tree(array, seg_tree, 0, 0, n - 1);

	int index, value;
	std::cin >> index >> value;
	update_tree(seg_tree, 0, 0, n - 1, index, value);

	for(auto x : seg_tree){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}