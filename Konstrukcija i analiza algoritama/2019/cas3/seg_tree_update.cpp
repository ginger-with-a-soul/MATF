#include <iostream>
#include <vector>
#include <cmath>

void build_seg_tree(std::vector<int>& array, std::vector<int>& tree, int x, int y, int k){
    if(x == y){
        tree[k] = array[x];
        return;
    }

    int middle = (x + y) / 2;

    build_seg_tree(array, tree, x, middle, 2*k);
    build_seg_tree(array, tree, middle+1, y, 2*k + 1);

    tree[k] = tree[2*k] + tree[2*k + 1];
}

void update_seg_tree(std::vector<int>& array, std::vector<int>& tree, int x, int y, int index, int new_value, int k){
    if(x == y){
        tree[k] = new_value;
        return;
    }

    int middle = (x + y) / 2;

    if(index <= middle){
        update_seg_tree(array, tree, x, middle, index, new_value, 2*k);
    }
    else{
        update_seg_tree(array, tree, middle+1, y, index, new_value, 2*k + 1);
    }

    tree[k] = tree[2*k] + tree[2*k + 1];
}

int main(){

    int n;
    std::cin >> n;
    std::vector<int> array(n);

    for(int i = 0; i < n; i++){
        std::cin >> array[i];
    }

    int h = ceil(log2(n));
    int seg_tree_size = 2 * pow(2, h);

    std::vector<int> tree(seg_tree_size);

    build_seg_tree(array, tree, 0, n - 1, 1);

    for(int x : tree){
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cout << "What index in tree do you want to update: ";
    int new_value, index;
    std::cin >> index;
    std::cout << "With what value: ";
    std::cin >> new_value;

    update_seg_tree(array, tree, 0, n - 1, index, new_value, 1);

    for(int x : tree){
        std::cout << x << " ";
    }
    std::cout << std::endl;

    exit(EXIT_SUCCESS);
}