#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>


void build_seg_tree(std::vector<std::tuple<int, int, int, bool>> &array,
					std::vector<std::tuple<int, int, int, bool>> &seg_tree,
					int k, int x, int y){

	if(x == y){
		std::get<0>(seg_tree[k]) = std::get<0>(array[x]);
		std::get<1>(seg_tree[k]) = std::get<1>(array[x]);
		std::get<2>(seg_tree[k]) = std::get<2>(array[x]);
		std::get<3>(seg_tree[k]) = std::get<3>(array[x]);
		return;
	}

	int middle = (x + y) / 2;

	build_seg_tree(array, seg_tree, 2 * k + 1, x, middle);
	build_seg_tree(array, seg_tree, 2 * k + 2, middle + 1, y);

	if(std::get<0>(seg_tree[2 * k + 1]) == -1 && std::get<0>(seg_tree[2 * k +2]) == -1){
		std::get<0>(seg_tree[k]) = -1;
		std::get<1>(seg_tree[k]) = -1;
		std::get<2>(seg_tree[k]) = 0;
		std::get<3>(seg_tree[k]) = false;
	}
	else if(std::get<0>(seg_tree[2 * k + 1]) == -1){
		std::get<0>(seg_tree[k]) = std::get<0>(seg_tree[2 * k + 2]);
		std::get<1>(seg_tree[k]) = std::get<1>(seg_tree[2 * k + 2]);
		std::get<2>(seg_tree[k]) = std::get<2>(seg_tree[2 * k + 2]);
		std::get<3>(seg_tree[k]) = std::get<3>(seg_tree[2 * k + 2]);
	}
	else if(std::get<0>(seg_tree[2 * k + 2]) == -1){
		std::get<0>(seg_tree[k]) = std::get<0>(seg_tree[2 * k + 1]);
		std::get<1>(seg_tree[k]) = std::get<1>(seg_tree[2 * k + 1]);
		std::get<2>(seg_tree[k]) = std::get<2>(seg_tree[2 * k + 1]);
		std::get<3>(seg_tree[k]) = std::get<3>(seg_tree[2 * k + 1]);

	}
	else{
		std::get<0>(seg_tree[k]) = std::max(std::get<0>(seg_tree[2 * k + 1]), std::get<0>(seg_tree[2 * k + 2]));
		std::get<1>(seg_tree[k]) = std::min(std::get<1>(seg_tree[2 * k + 1]), std::get<1>(seg_tree[2 * k + 2]));
		if((std::get<0>(seg_tree[k]) == std::get<0>(seg_tree[2 * k + 1]) && 
			std::get<1>(seg_tree[k]) == std::get<1>(seg_tree[2 * k + 1])) ||
		   (std::get<0>(seg_tree[k]) == std::get<0>(seg_tree[2 * k + 2]) && 
			std::get<1>(seg_tree[k]) == std::get<1>(seg_tree[2 * k + 2])) &&
			std::get<3>(seg_tree[2 * k + 1]) && std::get<3>(seg_tree[2 * k + 2])){
				std::get<3>(seg_tree[k]) = true;
			}
		else{
			std::get<3>(seg_tree[k]) = false;
		}
		std::get<2>(seg_tree[k]) = std::get<2>(seg_tree[2 * k + 1]) + std::get<2>(seg_tree[2 * k + 2]);
	}

}

int main(int argc, char** argv){

	int n; std::cin >> n;
	std::vector<std::tuple<int, int, int, bool>> array(n);

	for(int i = 0; i < n; i++){
		std::cin >> std::get<0>(array[i]) >> std::get<1>(array[i]);
		std::get<2>(array[i]) = 1;
		std::get<3>(array[i]) = true;
	}

	int height = ceil(log2(n));
	int size = 2 * pow(2, height) - 1;
	std::tuple<int, int, int, bool> x = {-1, -1, 0, false};
	std::vector<std::tuple<int, int, int, bool>> seg_tree(size, x);

	build_seg_tree(array, seg_tree, 0, 0, n - 1);

	for(auto t : seg_tree){
		if(std::get<3>(t)){
			std::cout << std::get<0>(t) << " " << std::get<1>(t) << " " << std::get<2>(t) - 1 << std::endl;
			break;
		}
	}

	exit(EXIT_SUCCESS);
}