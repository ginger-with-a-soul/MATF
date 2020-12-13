#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
unsigned pascal_triangle(unsigned n, unsigned k);

int main(int argc, char** argv){

	unsigned n, k; cin >> n >> k;

	cout << pascal_triangle(n, k) << "\n";

	exit(EXIT_SUCCESS);
}

unsigned pascal_triangle(unsigned n, unsigned k){

	vector<unsigned> dynamic(k + 1);
	dynamic[0] = 1;

	for(unsigned N = 1; N <= n; N++){
		if(N <= k){
			dynamic[N] = 1;
		}

		for(unsigned K = min(N - 1, k); K > 0; K--){
			dynamic[K] += dynamic[K - 1];
		}
	}

	return dynamic[k];
}