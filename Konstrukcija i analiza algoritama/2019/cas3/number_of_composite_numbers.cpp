#include <iostream>
#include <vector>
#include <cmath>

#define MAX_SIZE 10000

int number_of_complex(std::vector<int>& tree, int x, int y, int a, int b, int k){
    if(x > b || y < a){
        return 0;
    }

    if(x >= a && y <= b){
        return tree[k];
    }

    int middle = (x + y) / 2;

    return number_of_complex(tree, x, middle, a, b, 2*k) + number_of_complex(tree, middle+1, y, a, b, 2*k + 1);
}

void sieve_of_eratosthenes(std::vector<bool>& prime){
    prime[1] = true;

    for(int p = 2; p*p <= MAX_SIZE; p++){
        if(prime[p] == true){
            for(int i = p*2; i <= MAX_SIZE; i += p){
                prime[i] = false;
            }
        }
    }
}


void build_seg_tree(std::vector<int>& array, std::vector<int>& tree, int x, int y, int k){
    if(x == y){
        tree[k] = array[x];
    }

    int middle = (x + y) / 2;

    build_seg_tree(array, tree, x, middle, 2*k);
    build_seg_tree(array, tree, middle+1, y, 2*k + 1);

    tree[k] = tree[2*k] + tree[2*k + 1];
}


void update_tree(std::vector<int>& tree, int x, int y, int index, int difference, int k){
    if(x == y){
        tree[k] += difference;
    }

    int middle = (x + y) / 2;

    if(index <= middle){
        update_tree(tree, x, middle, index, difference, 2*k);
    }
    else{
        update_tree(tree, middle+1, y, index, difference, 2*k + 1);
    }

    tree[k] = tree[2*k] + tree[2*k + 1];
}


void update_array(std::vector<int>& array, std::vector<int>& tree, std::vector<bool>& prime, int y, int index, int new_value){
    int difference;

    int old_value = array[index];
    array[index] = new_value;

    if(prime[old_value] == prime[new_value]){
        return;
    }
    if(prime[old_value] && !prime[new_value]){
        difference = 1;
    }
    else{
        difference = -1;
    }

    update_tree(tree, 0, y, index, difference, 1);
}


int main(){

    int n;
    std::cin >> n;
    std::vector<int> array(n);

    for(int i = 0; i < n; i++){
        std::cin >> array[i];
    }

    std::cout << "Stigao";

    int h = ceil(log2(n));
    int tree_size = 2 * pow(2, h);
    std::vector<int> tree(tree_size);

    build_seg_tree(array, tree, 0, n - 1, 1);

    std::vector<bool> prime(MAX_SIZE);

    std::fill(prime.begin(), prime.end(), true);

    sieve_of_eratosthenes(prime);

    std::cout << "Input the range [a, b]: ";
    int a, b, index, new_value;
    std::cin >> a >> b;

    std::cout << number_of_complex(tree, 0, n - 1, a, b, 1) << std::endl;

    std::cout << "What index in array do you want to change and with what value: ";
    std::cin >> index >> new_value;

    update_array(array, tree, prime, n-1, index, new_value);

    std::cout << number_of_complex(tree, 0, n - 1, a, b, 1) << std::endl;

    exit(EXIT_SUCCESS);
}