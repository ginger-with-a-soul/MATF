#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int find(vector<int>& array, int x);

int main(int argc, char** argv){

	unsigned n; cin >> n;
	int x; cin >> x;
	vector<int> array(n);

	for(int i = 0; i < n; i++){
		cin >> array[i];
	}

	cout << find(array, x) << endl;

	exit(EXIT_SUCCESS);
}

int find(vector<int>& array, int x){
	int l = 0, r = array.size() - 1, m;

	while(l <= r){
		m = l + (r - l) / 2;
		if(array[m] == x){
			return m;
		}
		else if(array[l] < array[m - 1]){
			if(array[l] <= x && array[m - 1] >= x){
				r = m - 1;
			}
			else{
				l = m + 1;
			}
		}
		else{
			if(array[m + 1] <= x && array[r] >= x){
				l = m + 1;
			}
			else{
				r = m - 1;
			}
		}
	}
	return -1;

}