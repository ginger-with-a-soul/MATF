#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

struct Node {
    int largest;
    int secondLargest;
};

void bst(auto &tree, std::vector<int> &array, int x, int y, int k){
    if(x == y){
        tree[k].largest = array[x];
        tree[k].secondLargest = INT_MIN;
        return;
    }

    int middle = (x+y) / 2;

    bst(tree, array, x, middle, 2*k);
    bst(tree, array, middle+1, y, 2*k+1);

    tree[k].largest = std::max(tree[2*k].largest, tree[2*k+1].largest);
    tree[k].secondLargest = std::min(std::max(tree[2*k].largest, tree[2*k+1].secondLargest), std::max(tree[2*k].secondLargest, tree[2*k+1].largest));

}

Node fms(auto &tree, int x, int y, int k, int a, int b){
    Node result;
    result.largest = INT_MIN;
    result.secondLargest = INT_MIN;

    if(a > y || b < x){
        return result;
    }

    if(x >= a && y <= b){
        return tree[k];
    }

    int middle = (x+y) / 2;

    Node left = fms(tree, x, middle, 2*k, a, b);
    Node right = fms(tree, middle+1, y, 2*k+1, a, b);

    result.largest = std::max(left.largest, right.largest);
    result.secondLargest = std::min(std::max(left.largest, right.secondLargest), std::max(left.secondLargest, right.largest));

    return result;
}

int main(){
    std::vector<int> array = {1, 2, 3, 4, 5, 6}; int n = array.size(); int h = ceil(log2(n)); int size = 2*pow(2, h);
    std::vector<Node> tree(size);
    bst(tree, array, 0, n-1, 1);
    Node result = fms(tree, 0, n-1, 1, 1, 4);
    std::cout << result.largest << " is the largest; " << result.secondLargest << " is the 2nd largest" << std::endl;
    exit(EXIT_SUCCESS);
}