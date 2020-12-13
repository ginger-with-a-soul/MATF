#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int fib_memo(int n, vector<int>& array);


int main(int argc, char** argv){

	int n;
	cin >> n;

	vector<int>array(n + 1, -1);


	cout << fib_memo(n, array) << endl;

	exit(EXIT_SUCCESS);
}

int fib_memo(int n, vector<int>& array){

	if(array[n] != -1){
		return array[n];
	}

	if(n == 0){
		return array[n] = 0;
	}
	if(n == 1){
		return array[n] = 1;
	}

	return	array[n] = fib_memo(n - 1, array) + fib_memo(n - 2, array);
}