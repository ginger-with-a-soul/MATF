#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int quick_select(vector<int>& a, int l, int r, int x);

int main(int argc, char** argv){

	int n, x; cin >> n >> x;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	cout << quick_select(a, 0, a.size() - 1, x) << endl;

	exit(EXIT_SUCCESS);
}

int quick_select(vector<int>& a, int l, int r, int x){
	if(l < r){
		swap(a[l], a[l + rand() % (r - l + 1)]);
		int k = l;
		for(int i = l + 1; i <= r; i++){
			if(a[i] <= a[l]){
				swap(a[i], a[++k]);
			}
		}
		swap(a[l], a[k]);

		if(k == x){
			return a[k];
		}
		else if(x < k){
			return quick_select(a, l, k - 1, x);
		}
		else{
			return quick_select(a, k + 1, r, x);
		}
	}
}