#include <iostream>
#include <cmath>
#include <vector>

void segment_tree(std::vector<int> &array, std::vector<int> &tree, int k, int x, int y){
    
    if(x == y){
        tree[k] = array[x];
        return;
    }

    int middle = (x + y) / 2;

    segment_tree(array, tree, 2*k, x, middle);
    segment_tree(array, tree, 2*k + 1, middle + 1, y);

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

    int size = 2 * pow(2, h);

    std::vector<int> tree(size);

    segment_tree(array, tree, 1, 0, n - 1);

    for(int x : tree){
        std::cout << x << " ";
    }

    std::cout << std::endl;
}