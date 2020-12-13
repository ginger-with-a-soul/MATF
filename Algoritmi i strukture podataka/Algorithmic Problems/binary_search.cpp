/* Binary search - finding the element in an array that is sorted
 *
 * Average complexity is O(log*n) and the best case scenario is O(1) */

#include <iostream>
#include <vector>

void input(unsigned n, std::vector<int> &v);
unsigned binary_search(std::vector<int> &v, int x);

int main(){

	unsigned n = 0;
	int x = 0;
	std::vector<int> v;

	std::cin >> x;

	input(n, v);
	n = binary_search(v, x);

	if(n == v.size()){
		std::cout << "There in no element " << x << " in vector!\n";
	}
	else{
		std::cout << "Element " << x << " is at the position " << n << std::endl;
	}

	exit(EXIT_SUCCESS);
}

void input(unsigned n, std::vector<int> &v){

	std::cout << "Input the size of your vector: ";
	std::cin >> n;
	if(n < 1){
		std::cout << "\nInvalid vector size...\nTerminating!\n";
		exit(EXIT_SUCCESS);
	}
	v.resize(n);

	std::cout << "\nInput the elements of your vector: ";

	for(unsigned i = 0; i < n; i++){
		std::cin >> v[i];
	}

}

unsigned binary_search(std::vector<int> &v, int x){
	unsigned l = 0, r = v.size() - 1, p = 0;

	while(l <= r){
		p = l + (r - l) / 2;
		if(v[p] > x){
			r = p - 1;
		}
		else if(v[p] < x){
			l = p + 1;
		}
		else{
			return p;
		}
	}

	return v.size();

}
