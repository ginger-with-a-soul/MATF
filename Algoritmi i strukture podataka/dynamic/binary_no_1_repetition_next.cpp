#include <iostream>
#include <vector>

using namespace std;

bool next_bin(string& bin);

int main(){

	string bin = "01001";

	if(next_bin(bin)){
		cout << bin << endl;
	}

	exit(EXIT_SUCCESS);
}

bool next_bin(string& bin){

	int i = bin.size() - 1;
	while((i >= 0 && bin[i] == '1') || (i >= 1 && bin[i - 1] == '1')){
		bin[i] = '0';
		i--;
	}
	if(i < 0){
		return false;
	}
	else{
		bin[i] = '1';
		return true;
	}

}