#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void make_partitions(vector<int>& partitions, int n, int smax, int i);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> partitions(n);

	make_partitions(partitions, n, n, 0);

	

	exit(EXIT_SUCCESS);
}

void make_partitions(vector<int>& partitions, int n, int smax, int i){
	if(n == 0){
		for(int j = 0; j < i; j++){
			cout << partitions[j] << " ";
		}
		cout << endl;;
	}
	else{
		if(smax == 0){
			return;
		}
		make_partitions(partitions, n, smax - 1, i);
		if(n >= smax){
			partitions[i] = smax;
			make_partitions(partitions, n - smax, smax, i + 1);
		}
	}
}