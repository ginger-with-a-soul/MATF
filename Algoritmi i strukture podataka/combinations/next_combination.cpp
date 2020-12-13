	#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool exists_next_combination(vector<int>& comb, int n);

int main(int argc, char** argv){

	int n, k; cin >> n >> k;
	vector<int> comb(k);
	for(int i = 0; i < k; i++){
		comb[i] = i + 1;
	}

	do {
		for(int i = 0; i < k; i++){
			cout << comb[i] << " ";
		}
		cout << endl;
	} while(exists_next_combination(comb, n));

	exit(EXIT_SUCCESS);
}

bool exists_next_combination(vector<int>& comb, int n){
	int k = comb.size();
	int i = k - 1;

	for(; i >= 0 && comb[i] == n; i--, n--){}

	if(i < 0){
		return false;
	}
	
	comb[i++] += 1;

	while(i < k){
		comb[i] = comb[i - 1] + 1;
		i++;
	}

	return true;
}