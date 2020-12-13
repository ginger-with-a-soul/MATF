/* The program determines which 2 numbers are missing from the
 * array of Natural Numbers that do doesn't contain same elements */

#include <iostream>
#include <cmath>

int main(){

	unsigned n = 0;

	std::cout << "Input the upper limit of your array: ";
	std::cin >> n;
	if(n < 0){
		std::cout << "Invalid value...\nTerminating!\n";
		exit(EXIT_FAILURE);
	}

	unsigned sum = 0, sumSquared = 0, x = 0, c1 = 0, c2 = 0, f = 0, s = 0;

	std::cout << "Input your array that is missing two elements: ";
	for(unsigned i = 1; i < n; i++){
		std::cin >> x;
		sum += x;
		sumSquared += x * x;
	}

	c1 = n * (n + 1) / 2 - sum;
	c2 = n * (n + 1) * (2 * n + 1) / 6 - sumSquared;
	f = (c1 + sqrt(2 * c2 - c1 * c1)) / 2;
	s = c1 - f;

	std::cout << "Your missing elements are: " << f << " and " << s << std::endl;

	exit(EXIT_SUCCESS);
}