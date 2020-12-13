#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned dance_couples(vector<unsigned>& b, vector<unsigned>& g);

bool compare_func(unsigned x, unsigned y){
	return x > y;
}

int main(int argc, char** argv){

	unsigned n;
	cin >> n;
	vector<unsigned> b(n);
	vector<unsigned> g(n);

	for(int i = 0; i < n; i++){
		cin >> b[i];
	}

	for(int i = 0; i < n; i++){
		cin >> g[i];
	}

	sort(b.begin(), b.end(), compare_func);
	sort(g.begin(), g.end(), compare_func);

	for(int i = 0; i < n; i++){
		cout << b[i] << " ";
	}
	cout << endl;

	cout << dance_couples(b, g) << endl;

	exit(EXIT_SUCCESS);
}

unsigned dance_couples(vector<unsigned>& b, vector<unsigned>& g){
	unsigned size = b.size(), num = 0, g_pos = 0;

	for(int i = 0; i < size && g_pos < size;){
		if(b[i] <= g[g_pos]){
			g_pos += 1;
		}
		else{
			num += 1;
			g_pos += 1;
			i += 1;
		}
	}

	return num;
}