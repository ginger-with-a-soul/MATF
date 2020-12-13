/* The program for sorting the elements of an array in a way that
 * first [0, N) are negative numbers, [N, i) are zeros, [i, P) are unidentified values,
 * [P, n) are positive numbers.
 *
 * The order of these numbers is not defined.
 *
 * Complexity of The Dutch National Flag problem is O(n) */

#include <iostream>
#include <vector>

void input(unsigned n, std::vector<int> &v);
void dutch_flag(std::vector<int> &v);
void output(std::vector<int> &v);

int main() {

	unsigned n = 0;
	std::vector<int> v;

	input(n, v);
	dutch_flag(v);
	output(v);

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

void dutch_flag(std::vector<int> &v){

	unsigned n = v.size();
	unsigned i = 0, N = 0, P = n;

	while(i < P){
		if(v[i] > 0){
			std::swap(v[i], v[--P]);
		}
		else if(v[i] < 0){
			std::swap(v[i++], v[N++]);
		}
		else{
			i++;
		}
	}

}

void output(std::vector<int> &v){

	unsigned n = v.size();

	std::cout << "Resulting vector: ";

	for(unsigned i = 0; i < n; i++){
		std::cout << v[i] << " ";
	}

}