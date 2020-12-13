#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Node {
    int greatestCommonDivider;
    int min;
    int counter;
};

void build_tree(std::vector<int> &array, std::vector<Node> &tree, int x, int y, int k){
    if(x == y){
        tree[k].greatestCommonDivider = array[x];
        tree[k].counter = 1;
        tree[k].min = array[x];
        return ;
    }

    int middle = (x + y) / 2;

    build_tree(array, tree, x, middle, 2*k);
    build_tree(array, tree, middle+1, y, 2*k + 1);

    tree[k].greatestCommonDivider = std::__gcd(tree[2*k].greatestCommonDivider, tree[2*k + 1].greatestCommonDivider);

    if(tree[2*k].min < tree[2*k + 1].min){
        tree[k].min = tree[2*k].min;
        tree[k].counter = tree[2*k].counter;
    }
    else if(tree[2*k].min > tree[2*k + 1].min){
        tree[k].min = tree[2*k + 1].min;
        tree[k].counter = tree[2*k + 1].counter;
    }
    else{
        tree[k].greatestCommonDivider = tree[2*k].greatestCommonDivider;
        tree[k].counter = tree[2*k].counter + tree[2*k + 1].counter;
    }
}

Node count_dividers(std::vector<Node> &tree, int x, int y, int a, int b, int k){
    Node result;

    if(x > b || y < a){
        result.counter = 0;
        result.greatestCommonDivider = 0;
        result.min = 0;
        return result;
    }

    if(x >= a && y <= b){
        result.greatestCommonDivider = tree[k].greatestCommonDivider;
        result.min = tree[k].min;

        if(result.min != result.greatestCommonDivider){
            result.counter = 0;
        }
        else{
            result.counter = tree[k].counter;
        }
        return result;
    }

    int middle = (x + y) / 2;

    Node left = count_dividers(tree, x, middle, a, b, 2*k);
    Node right = count_dividers(tree, middle+1, y, a, b, 2*k + 1);

    if(left.greatestCommonDivider && right.greatestCommonDivider){
        result.greatestCommonDivider = std::__gcd(left.greatestCommonDivider, right.greatestCommonDivider);
        int min = std::min(left.min, right.min);

        if(result.greatestCommonDivider != min){
            result.greatestCommonDivider = 0;
            result.min = 0;
            result.counter = 0;
        }
        else{
            if(left.min = right.min){
                result.min = left.min;
                result.counter = left.counter + right.counter;
            }
            else if(left.min < right.min){
                result.min = left.min;
                result.counter = left.counter;
            }
            else{
                result.min = right.min;
                result.counter = right.counter;
            }
        }
        return result;
    }
    else if(left.greatestCommonDivider){
        return left;
    }
    else if(right.greatestCommonDivider){
        return right;
    }
}

int main(){

    int n; std::cin >> n; std::vector<int> array(n);
    for(int i = 0; i < n; i++){
        std::cin >> array[i];
    }
    int h = ceil(log2(n)), treeSize = 2 * pow(2, h);
    std::vector<Node> tree(treeSize);

    build_tree(array, tree, 0, n - 1, 1);

    int a, b; std::cout << "Insert [a,b] range: "; std::cin >> a >> b;

    Node result = count_dividers(tree, 0, n - 1, a, b, 1);

    std::cout << result.greatestCommonDivider << std::endl << result.counter << std::endl;

    exit(EXIT_SUCCESS);
}