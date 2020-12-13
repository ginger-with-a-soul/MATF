#include <iostream>
#include <vector>
#include <cmath>

void build_seg_tree(std::vector<int> &array, std::vector<int> &seg_tree, int k, int x, int y, bool op){
	if(x == y){
		seg_tree[k] = array[x];
		return;
	}

	int middle = (x + y) / 2;
	build_seg_tree(array, seg_tree, 2 * k + 1, x, middle, !op);
	build_seg_tree(array, seg_tree, 2 * k + 2, middle + 1, y, !op);

	if(op){
		seg_tree[k] = seg_tree[2 * k + 1] ^ seg_tree[2 * k + 2];
	}
	else{
		seg_tree[k] = seg_tree[2 * k + 1] | seg_tree[2 * k + 2];
	}
}

void update_tree(std::vector<int> &seg_tree, int k, int x, int y, int index, int value, bool op){
	if(x == y){
		seg_tree[k] = value;
		return;
	}

	int middle = (x + y) / 2;
	if(index <= middle){
		update_tree(seg_tree, 2 * k + 1, x, middle, index, value, !op);
	}
	else{
		update_tree(seg_tree, 2 * k + 2, middle + 1, y, index, value, !op);
	}

	if(op){
		seg_tree[k] = seg_tree[2 * k + 1] ^ seg_tree[2 * k + 2];
	}
	else{
		seg_tree[k] = seg_tree[2 * k + 1] | seg_tree[2 * k + 2];
	}
	
}

int main(int argc, char** argv){

	int n, 	q;
	std::cin >> n >> q;
	int array_size = pow(2, n);
	std::vector<int> array(array_size);

	int height = ceil(log2(array_size));
	int size = 2 * pow(2, height) - 1;
	std::vector<int> seg_tree(size);

	for(int i = 0; i < array_size; i++){
		std::cin >> array[i];
	}

	bool op = true;
	build_seg_tree(array, seg_tree, 0, 0, array_size - 1, op);

	int index, value;
	for(int i = 0; i < q; i++){
		std::cin >> index >> value;
		update_tree(seg_tree, 0, 0, array_size - 1, index, value, op);
		std::cout << seg_tree[0] << std::endl;
	}

	exit(EXIT_SUCCESS);
}