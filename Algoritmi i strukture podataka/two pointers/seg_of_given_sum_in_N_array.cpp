#include <iostream>
#include <vector>

using namespace std;

void find_segment(vector<int>& a, int x);

int main(int argc, char** argv){

	int x;
	cin >> x;

	unsigned n;
	cin >> n;
	vector<int> a(n);

	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	find_segment(a, x);

	exit(EXIT_SUCCESS);
}

void find_segment(vector<int>& a, int x){

	unsigned size = a.size();
	vector<int> ps(size + 1);
	ps[0] = 0;
	for(int i = 1; i < size + 1; i++){
		ps[i] = ps[i - 1] + a[i - 1];
	}

	for(int i = 0, j = 1; j < size + 1; ){
		if(ps[j] - ps[i] > x){
			i++;
		}
		else if(ps[j] - ps[i] < x){
			j++;
		}
		else{
			cout << i << " " << j - 1 << endl;
			i++;
		}
	}

}