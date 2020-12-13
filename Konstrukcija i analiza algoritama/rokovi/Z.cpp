#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> find_Z(std::string &haystack){
	int l = 0, d = 0;
	int n = haystack.size();

	std::vector<int> Z_vector(n);
	for(int i = 1; i < n; i++){
		if(i <= d){
			Z_vector[i] = std::min(Z_vector[i - l], d - i + 1);
		}

		while(i + Z_vector[i] < n && haystack[Z_vector[i]] == haystack[Z_vector[i] + i]){
			Z_vector[i]++;
		}

		if(i + Z_vector[i] - 1 > d){
			l = i;
			d = i + Z_vector[i] - 1;
		}
	}

	return Z_vector;
}

int main(int argc, char** argv){

	std::string needle, haystack; std::cin >> needle >> haystack;

	haystack = needle + "#" + haystack;

	std::vector<int> Z_vector = find_Z(haystack);
	int n = haystack.size();
	int m = needle.size();

	for(int i = 0; i < n; i++){
		if(Z_vector[i] == m){
			std::cout << i - m - 1 << " ";
		}
	}
	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}