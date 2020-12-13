#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

struct Node {
	int lrg;
	int sec_lrg;
};

void build_seg_tree(std::vector<int> &array, std::vector<Node> &seg_tree, int k, int x, int y){
	if(x == y){
		seg_tree[k].lrg = array[x];
		seg_tree[k].sec_lrg = INT_MIN;
		return;
	}

	int middle = (x + y) / 2;
	build_seg_tree(array, seg_tree, 2 * k + 1, x, middle);
	build_seg_tree(array, seg_tree, 2 * k + 2, middle + 1, y);

	seg_tree[k].lrg = std::max(seg_tree[2 * k + 1].lrg, seg_tree[2 * k + 2].lrg);
	seg_tree[k].sec_lrg = std::min(std::max(seg_tree[2 * k + 1].lrg, seg_tree[2 * k + 2].sec_lrg),
								   std::max(seg_tree[2 * k + 1].sec_lrg, seg_tree[2 * k + 2].lrg));
	
}

void update_tree(std::vector<Node> &seg_tree, int k, int x, int y, int index, int value){
	if(x == y){
		seg_tree[k].lrg = value;
		return;
	}

	int middle = (x + y) / 2;

	if(index <= middle){
		update_tree(seg_tree, 2 * k + 1, x, middle, index, value);
	}
	else{
		update_tree(seg_tree, 2 * k + 2, middle + 1, y, index, value);
	}

	seg_tree[k].lrg = std::max(seg_tree[2 * k + 1].lrg, seg_tree[2 * k + 2].lrg);
	seg_tree[k].sec_lrg = std::min(std::max(seg_tree[2 * k + 1].lrg, seg_tree[2 * k + 2].sec_lrg),
								   std::max(seg_tree[2 * k + 1].sec_lrg, seg_tree[2 * k + 2].lrg));

}

void update_array(std::vector<int> &array, std::vector<Node> &seg_tree, int n, int index, int value){
	array[index] = value;

	update_tree(seg_tree, 0, 0, n - 1, index, value);
}

Node find_max_product(std::vector<Node> &seg_tree, int k, int x, int y, int a, int b){

	Node tmp;
	tmp.lrg = INT_MIN;
	tmp.sec_lrg = INT_MIN;

	if(x > b || y < a){
		return tmp;
	}

	if(x >= a && y <= b){
		return seg_tree[k];
	}

	int middle = (x + y) / 2;

	Node left =  find_max_product(seg_tree, 2 * k + 1, 0, middle, a, b);
	Node right = find_max_product(seg_tree, 2 * k + 2, middle + 1, y, a, b);

	tmp.lrg = std::max(left.lrg, right.lrg);
	tmp.sec_lrg = std::min(std::max(left.lrg, right.sec_lrg), std::max(left.sec_lrg, right.lrg));

	return tmp;
}

int main(int argc, char** argv){

	std::vector<int> array = {3, 4, 1, 2, 6, 5, 1, 4};
	int n = array.size();

	int height = ceil(log2(n));
	int size = 2 * pow(2, height) - 1;
	std::vector<Node> seg_tree(size);

	build_seg_tree(array, seg_tree, 0, 0, n - 1);
	
	int index, value;
	std::cin >> index >> value;
	update_array(array, seg_tree, n, index, value);

	int a, b;
	std::cin >> a >> b;

	Node result = find_max_product(seg_tree, 0, 0, n - 1, a, b);

	std::cout << "Max product: " << result.lrg * result.sec_lrg << std::endl;

	exit(EXIT_SUCCESS);
}