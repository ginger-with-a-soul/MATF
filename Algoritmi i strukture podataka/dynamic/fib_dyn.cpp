#include <iostream>

using namespace std;

long long fib_dyn(long long n);

int main(){

	long long n;
	cin >> n;

	cout << fib_dyn(n) << endl;

	exit(EXIT_SUCCESS);
}

long long fib_dyn(long long n){
	long long pp = 0;
	if(n == 0){
		return pp = 0;
	}
	long long p = 1;
	if(n == 1){
		return p = 1;
	}
	for(int i = 2; i <= n; i++){
		long long f = pp + p;
		pp = p;
		p = f;
	}
	return p;
}