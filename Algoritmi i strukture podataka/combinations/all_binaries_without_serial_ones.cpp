#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool has_next_var(vector<int>& var, int n);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> var(n, 0);

	while(has_next_var(var, n)){
		for(int i = 0; i < n; i++){
			cout << var[i] << " ";
		}
		cout << endl;
	}

	exit(EXIT_SUCCESS);
}

bool has_next_var(vector<int>& var, int n){
	int k = n - 1;
	for(; (k >= 0 && var[k] == 1) || (k > 0 && var[k - 1] == 1); k--){
		var[k] = 0;
	}

	if(k < 0){
		return false;
	}
	else{
		var[k] = 1;
		return true;
	}
}