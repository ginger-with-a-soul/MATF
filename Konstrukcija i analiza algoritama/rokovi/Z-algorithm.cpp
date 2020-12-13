#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> find_Z_array(std::string &haystack){
	int n = haystack.size();
	std::vector<int> Z_array(n);

	int d = 0, l = 0;
	Z_array[0] = 0;

	for(int i = 1; i < n; i++){
		if(i <= d){
			Z_array[i] = std::min(Z_array[i - l], d - i + 1);
		}

		while(i + Z_array[i] < n && haystack[Z_array[i]] == haystack[Z_array[i] + i]){
			Z_array[i]++;
		}

		if(i + Z_array[i] - 1 > d){
			l = i;
			d = i + Z_array[i] - 1;
		}
	}

	return Z_array;
}

int main(int argc, char** argv){

	std::string needle, haystack; std::cin >> needle >> haystack;
	haystack = needle + '#' + haystack;

	std::vector<int> Z_array = find_Z_array(haystack);

	int n = haystack.size();
	int m = needle.size();

	for(int i = 0; i < n; i++){
		if(Z_array[i] == m){
			std::cout << i - m - 1 << " ";
		}
	}

	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}