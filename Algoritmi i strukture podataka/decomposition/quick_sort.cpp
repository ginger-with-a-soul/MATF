#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void quick_sort(vector<int>& a, int l, int r);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	quick_sort(a, 0, a.size() - 1);

	for(int x : a){
		cout << x << " ";
	}

	cout << endl;

	exit(EXIT_SUCCESS);
}

void quick_sort(vector<int>& a, int l, int r){
	if(l < r){
		swap(a[l], a[l + rand() % (r - l + 1)]);

		int k = l;
		for(int i = l + 1; i <= r; i++){
			if(a[i] <= a[l]){
				swap(a[i], a[++k]);
			}
		}
		swap(a[l], a[k]);
		
		quick_sort(a, l, k - 1);
		quick_sort(a, k + 1, r);
	}
}