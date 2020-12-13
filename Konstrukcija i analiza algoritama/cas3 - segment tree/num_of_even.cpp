#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void build_seg_tree(std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y){

	if(x == y){
		if(array[x] % 2){
			segment_tree[k] = 0;
		}
		else{
			segment_tree[k] = 1;
		}
		return;
	}

	int middle = (x + y) / 2;

	build_seg_tree(array, segment_tree, 2 * k + 1, x, middle);
	build_seg_tree(array, segment_tree, 2 * k + 2, middle + 1, y);

	segment_tree[k] = segment_tree[2 * k + 1] + segment_tree[2 * k + 2];
}

int count_even(std::vector<int> &segment_tree, int k, int x, int y, int a, int b){

	if(x > b || y < a){
		return 0;
	}

	if(x >= a && y <= b){
		return segment_tree[k];
	}

	int middle = (x + y) / 2;
	
	return count_even(segment_tree, 2 * k + 1, x, middle, a, b) + count_even(segment_tree, 2 * k + 2, middle + 1, y, a, b);
}

int main(int argc, char** argv){

	std::vector<int> array = {3, 4, 1, 2, 6, 5, 1, 4};
	int n = array.size();
	
	int height = ceil(log2(n));
	int size = 2 * pow(2, height) - 1;

	std::vector<int> segment_tree(size);
	build_seg_tree(array, segment_tree, 0, 0, n - 1);

	int a, b;
	std::cin >> a >> b;

	std::cout << count_even(segment_tree, 0, 0, n - 1, a, b) << std::endl;

	exit(EXIT_SUCCESS);
}