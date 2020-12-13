#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

struct Node {

    int largest;
    int second_largest;

};

Node find_max_product(std::vector<Node>& tree, int x, int y, int a, int b, int k){
    Node result, left, right;

    result.largest = INT_MIN;
    result.second_largest = INT_MIN;

    if(x > b || y < a){
        return result;
    }

    if(x >= a || y <= b){
        return tree[k];
    }

    int middle = (x + y) / 2;

    left = find_max_product(tree, x, middle, a, b, 2*k);
    right = find_max_product(tree, middle+1, y, a, b, 2*k + 1);

    result.largest = std::max(left.largest, right.largest);
    result.second_largest = std::min(std::max(left.largest, right.second_largest),
                                     std::max(left.second_largest, right.largest));

    return result;
}

void build_seg_tree(std::vector<int>& array, std::vector<Node>& tree, int x, int y, int k){
    if(x == y){
        tree[k].largest = array[x];
        tree[k].second_largest = INT_MIN;
    }

    int middle = (x + y) / 2;

    build_seg_tree(array, tree, x, middle, 2*k);
    build_seg_tree(array, tree, middle+1, y, 2*k +1);

    tree[k].largest = std::max(tree[2*k].largest, tree[2*k + 1].largest);
    tree[k].second_largest = std::min((std::max(tree[2*k].largest, tree[2*k + 1].second_largest)),
                                       std::max(tree[2*k].second_largest, tree[2*k + 1].largest));
}

void update_tree(std::vector<Node>& tree, int x, int y, int index, int new_value, int k){
    if(x == y){
        tree[k].largest = new_value;
        tree[k].second_largest = INT_MIN;
    }

    int middle = (x + y) / 2;

    if(index <= middle){
        update_tree(tree, x, middle, index, new_value, 2*k);
    }
    else{
        update_tree(tree, middle+1, y, index, new_value, 2*k + 1);
    }

    tree[k].largest = std::max(tree[2*k].largest, tree[2*k + 1].largest);
    tree[k].second_largest = std::min(std::max(tree[2*k].largest, tree[2*k + 1].second_largest), 
                                      std::max(tree[2*k].second_largest, tree[2*k + 1].largest));
}

void update_array(std::vector<int>& array, std::vector<Node>& tree, int x, int y, int index, int new_value, int k){
    array[index] = new_value;

    update_tree(tree, x, y, index, new_value, k);
}

int main(){

    int n; std::cin >> n; std::vector<int> array(n);
    for(int i = 0; i < n; i++){
        std::cin >> array[i];
    }

    int h = ceil(log2(n)), tree_size = 2 * pow(2, h);
    std::vector<Node> tree(tree_size);

    build_seg_tree(array, tree, 0, n - 1, 1);

    std::cout << "Input the segment [a, b]: "; int a, b; std::cin >> a >> b;

    Node result = find_max_product(tree, 0, n - 1, a, b, 1); std::cout << result.largest * result.second_largest << std::endl;

    std::cout << "Index that you want to change and with what value: "; int index, new_value; std::cin >> index >> new_value;

    update_array(array, tree, 0, n - 1, index, new_value, 1);

    result = find_max_product(tree, 0, n - 1, a, b, 1); std::cout << result.largest * result.second_largest << std::endl;

    exit(EXIT_SUCCESS);
}