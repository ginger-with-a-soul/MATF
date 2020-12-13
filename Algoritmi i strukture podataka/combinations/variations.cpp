#include <iostream>
#include <vector>

using namespace std;

void gen_var(vector<int>&array, int n, int k);

int main(){

	int n, k;
	cin >> n >> k;
	vector<int> array(k, 0);

	gen_var(array, n, k);

}

void gen_var(vector<int>&array, int n, int k){

	if(k == 0){
		for(int i = 0; i < array.size(); i++){
			cout << array[i] << " ";
		}
		cout << endl;
		return;
	}

	for(int i = 0; i < n; i++){
		array[array.size() - k] = i;
		gen_var(array, n, k - 1);
	}
}