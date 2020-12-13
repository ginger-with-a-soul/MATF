/* The program identifies what number is missing from the
 * set of Natural Numbers starting from n to m [n, m].
 * It could be used in O(1) to summarize [n, m] numbers
 * or in O(m - n) to find a missing number*/

#include <iostream>

int main() {

	unsigned x = 0;
	unsigned n = 0;
	unsigned m = 0;

	std::cout << "Insert the lower bound of your set: ";
	std::cin >> n;
	std::cout << "Insert the upper bound of your set: ";
	std::cin >> m;

	if(n < 0 || n >= m){
		std::cout << "Invalid values...\nTerminating!\n";
		exit(EXIT_FAILURE);
	}

	double wholeSum = m * ((m + 1) / 2);//This order sometimes prevents exceeding the size of double when multiplying
	double lowerSum = n * ((double)(n + 1) / 2.0);
	unsigned difference = wholeSum - lowerSum;

	unsigned n_to_m_sum = 0;

	std::cout << "Insert numbers [n, m] without duplicating any and skipping one that you want: ";
	for(unsigned i = n; i < m; i++){
		std::cin >> x;
		n_to_m_sum += x;
	}

	unsigned including_n = difference + n;

	std::cout << "The missing number is: " << including_n - n_to_m_sum << std::endl;

	exit(EXIT_SUCCESS);
}