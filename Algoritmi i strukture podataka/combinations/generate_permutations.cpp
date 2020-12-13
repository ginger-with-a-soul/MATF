#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void generate_permutations(vector<int>& perm, int n);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> perm(n);

	for(int i = 0; i < n; i++){
		perm[i] = i + 1;
	}

	generate_permutations(perm, n);

	exit(EXIT_SUCCESS);
}

void generate_permutations(vector<int>& perm, int n){
	if(n == 1){
		for(int i = 0; i < perm.size(); i++){
			cout << perm[i] << " ";
		}
		cout << endl;
		return;
	}
	else{
		for(int i = 0; i < n; i++){
			swap(perm[i], perm[n - 1]);
			generate_permutations(perm, n - 1);
			swap(perm[i], perm[n - 1]);
		}
	}
}