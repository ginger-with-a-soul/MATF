#include <iostream>
#include <vector>

int main(){
	unsigned n;
	std::cin >> n;
	if(n < 0){
		std::cerr << "Invalid input...\nTerminating!\n";
		exit(EXIT_FAILURE);
	}
	std::vector<int> v(32);
	for(int i = 0; n > 0; i++, n /= 2){
		v[i] = n % 2;
	}
	auto rbeg = v.rbegin();
	auto rend = v.rend();

	for(;rbeg != rend; ++rbeg){
		std::cout << *rbeg << " ";
	}
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}