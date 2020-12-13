#include <iostream>
#include <vector>

using namespace std;

void binary_no1(string& bin, int i);
int main(){

	int k;
	cin >> k;

	string bin(k, '0');

	binary_no1(bin, 0);
	
}

void binary_no1(string& bin, int i){

	if(i == bin.size()){
		cout << bin << " ";
		cout << endl;
		return;
	}

	bin[i] = '0';
	binary_no1(bin, i + 1);
	if(i == 0 || bin[i - 1] != '1'){
		bin[i] = '1';
		binary_no1(bin, i + 1);
	}
}