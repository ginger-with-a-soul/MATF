#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int next_var(vector<int>& var, int n);

int main(int argc, char** argv){

	int n = 3, k, x; cin >> k;
	vector<int> var(k, 1);

	while((x = next_var(var, n))){
		if(x == 1){
			for(auto y : var){
				cout << y << " ";
			}
			cout << endl;
		}
	}

	exit(EXIT_SUCCESS);
}

int next_var(vector<int>& var, int n){
	int i = var.size() - 1;
	int k = var.size();

	for(; i >= 0 && var[i] == n; i--){}

	if(i < 0){
		return 0;
	}

	var[i++] += 1;
	while(i < k){
		var[i++] = 1;
	}

	i = k - 2;
	for(; i >= 0 && var[i] != var[i+1]; i--){}

	if(i < 0){
		return 1;
	}
	else{
		return -1;
	}
}