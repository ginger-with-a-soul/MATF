#include <iostream>
#include <vector>

using namespace std;

bool find_in_double_sorted_matrix(vector<vector<int>>& matrix, int x);

int main(int argc, char** argv){

	
	unsigned m, n;
	int x;
	cin >> x;
	cin >> m >> n;
	vector<vector<int> > matrix(m);

	for(int i = 0; i < m; i++){
		matrix[i].resize(n);
		for(int j = 0; j < n; j++){
			cin >> matrix[i][j];
		}
	}

	cout << boolalpha << find_in_double_sorted_matrix(matrix, x) << endl;

	exit(EXIT_SUCCESS);
}

bool find_in_double_sorted_matrix(vector<vector<int>>& matrix, int x){
	unsigned m = matrix.size(), n = matrix[0].size();
	unsigned v = m - 1, k = 0;
	
	while(v >= 0 && k < n){
		if(matrix[v][k] > x){
			v -= 1;
		}
		else if(matrix[v][k] < x){
			k += 1;
		}
		else{
			return true;
		}
	}

	return false;
}