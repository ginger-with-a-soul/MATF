#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void generate_variations(vector<int>& var, int k, int n);

int main(int argc, char** argv){

	int k, n; cin >> k >> n;
	vector<int> var(k);
	
	generate_variations(var, k, n);

	exit(EXIT_SUCCESS);
}

void generate_variations(vector<int>& var, int k, int n){
	if(k == 0){
		for(int i = 0; i < var.size(); i++){
			cout << var[i] << " ";
		}
		cout << endl;
		return;
	}

	for(int x = 1; x <= n; x++){
		var[var.size() - k] = x;
		generate_variations(var, k - 1, n);
	}
}