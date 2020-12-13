#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool is_hiccuping_substr(string& mainstr, string& substr, int n);
int longest_hiccuping_substr(string& mainstr, string& substr);

int main(int argc, char** argv){

	string mainstr, substr;
	cin >> mainstr >> substr;

	cout << longest_hiccuping_substr(mainstr, substr) << endl;

	exit(EXIT_SUCCESS);
}

bool is_hiccuping_substr(string& mainstr, string& substr, int n){
	int i = 0;
	for(char c : substr){
		for(int k = 0; k < n; k++){
			while(i < mainstr.size() && mainstr[i] != c){
				i += 1;
			}
			if(i == mainstr.size()){
				return false;
			}
			i += 1;
		}
	}
	
	return true;
}

int longest_hiccuping_substr(string& mainstr, string& substr){
	int l = 0, r = mainstr.size() / substr.size(), m;

	while(l <= r){
		m = l + (r - l) / 2;
		if(is_hiccuping_substr(mainstr, substr, m)){
			l = m + 1;
		}
		else{
			r = m - 1;
		}
	}
	return r;
}