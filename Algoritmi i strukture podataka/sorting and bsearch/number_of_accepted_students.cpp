#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void number(vector<int>& array, unsigned m);

int main(int argc, char** argv){

	unsigned n, m; cin >> n >> m;
	vector<int> array(n);

	for(int i = 0; i < n; i++){
		cin >> array[i];
	}

	sort(array.begin(), array.end());

	number(array, m);

	exit(EXIT_SUCCESS);
}

void number(vector<int>& array, unsigned m){
	unsigned x;

	for(int i = 0; i < m; i++){
		cin >> x;
		auto it = lower_bound(array.begin(), array.end(), x);
		cout << distance(it, array.end()) << endl;
	}

}