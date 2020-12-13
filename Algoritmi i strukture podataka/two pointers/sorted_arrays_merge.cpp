#include <iostream>
#include <vector>

using namespace std;

void two_pointer_merge(vector<int>& a1, vector<int>& a2, vector<int>& a3);

int main(int argc, char** argv){

	cout << "Input sizes of a1 and a2: " << endl;
	unsigned n, m;

	cin >> n >> m;
	vector<int> a1(n);
	vector<int> a2(m);
	vector<int> a3(n + m);
	for(int i = 0; i < n; i++){
		cin >> a1[i];
	}

	for(int i = 0; i < m; i++){
		cin >> a2[i];
	}

	two_pointer_merge(a1, a2, a3);

	for(auto it = a3.begin();  it != a3.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	exit(EXIT_SUCCESS);
}

void two_pointer_merge(vector<int>& a1, vector<int>& a2, vector<int>& a3){
	unsigned totalEl = a1.size() + a2.size(), i = 0, j = 0, k = 0;
	while(k < totalEl){
		if(i == a1.size()){
			a3[k++] = a2[j++];
		}
		else if(j == a1.size()){
			a3[k++] = a1[i++];
		}
		else{
			if(a1[i] >= a2[j]){
				a3[k++] = a1[i++];
			}
			else{
				a3[k++] = a2[j++];
			}
		}
	}
}