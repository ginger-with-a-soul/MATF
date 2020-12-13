#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int next_var(vector<int>& var, int n);

int main(int argc, char** argv){

	int n = 2, k, x = 1, num = 0; cin >> k;
	vector<int> var(k, 1);

	do {
		num = 0;
		if(x == 1){
			for(auto y : var){
				if(y == 1){
					cout << 'c';
				}
				else{
					num += 1;
					cout << 'p';
				}
			}
			cout << " " << num << endl;
		}
	} while((x = next_var(var, n)));

	exit(EXIT_SUCCESS);
}

int next_var(vector<int>& var, int n){
	int k = var.size();
	int i = k - 1;

	for(; i >= 0 && var[i] == n; i--){}

	if(i < 0){
		return 0;
	}

	var[i++] += 1;
	while(i < k){
		var[i++] = 1;
	}

	i = k - 2;
	while(i >= 0){
		if(var[i] == 2 && var[i + 1] == 2){
			return -1;
		}
		i -= 1;
	}

	return 1;
}