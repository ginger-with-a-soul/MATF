/* The program counts the number of elements from the Natural Array [a, b]
 * that divide a certain number in O(1) */

#include <iostream>
#include <cmath>

int main(){

	unsigned a = 0, b = 0, k = 0;

	std::cout << "Input lower and upper array limits: ";
	std::cin >> a >> b;

	if(a > b){
		std::cout << "Invalid values...\nTerminating!\n";
		exit(EXIT_FAILURE);
	}

	std::cout << "Input the element to be divided by: ";
	std::cin >> k;

	if(k < 1){
		std::cout << "Invalid value...\nTerminating!\n";
		exit(EXIT_FAILURE);
	}

	unsigned nr = b / k;
	unsigned nl = a == 0? 1 : ceil((double) a / (double) k);

	std::cout << "The number of elements between [" << a << ", " << b << "] that can be divided by " << k << " is: " << nr - nl + 1 << std::endl;



	exit(EXIT_SUCCESS);
}