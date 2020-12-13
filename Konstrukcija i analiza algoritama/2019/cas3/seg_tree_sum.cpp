#include <iostream>
#include <vector>
#include <cmath>

void build_seg_tree(std::vector<int>& array, std::vector<int>& tree, int k, int x, int y){

    if(x == y){
        tree[k] = array[x];
        return;
    }

    int middle = (x + y) / 2;

    build_seg_tree(array, tree, 2*k, x, middle);
    build_seg_tree(array, tree, 2*k + 1, middle+1, y);

    tree[k] = tree[2*k] + tree[2*k + 1];
}

int sum_seg(std::vector<int>& tree, int x, int y, int a, int b, int k){
    if(x > b || y < a){
        return 0;
    }

    if(x >= a && y <= b){
        return tree[k];
    }

    int middle = (x + y) / 2;

    return sum_seg(tree, x, middle, a, b, 2*k) + sum_seg(tree, middle+1, y, a, b, 2*k + 1);
}

int main(){

    int a, b, n;
    std::cout << "Unesite velicinu niza: ";
    std::cin >> n;

    std::vector<int> array(n);

    for(int i = 0; i < n; i++){
        std::cin >> array[i];
    }

    std::cout << "Unesite brojeve a i b: ";
    std::cin >> a >> b;

    int h = ceil(log2(n));
    int size = 2 * pow(2, h);

    std::vector<int> tree(size);

    if(a < 0 || b > n - 1){
        std::cout << "Bad input!";
        exit(EXIT_FAILURE);
    }

    build_seg_tree(array, tree, 1, 0, n - 1);

    std::cout << sum_seg(tree, 0, n - 1, a, b, 1) << std::endl;

    exit(EXIT_SUCCESS);
}