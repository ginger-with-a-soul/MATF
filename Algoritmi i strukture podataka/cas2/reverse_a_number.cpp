#include <iostream>

int main(){
	int n;
	int res = 0;
	unsigned leadZero = 0;
	bool sign = false;

	std::cin >> n;
	
	if(n < 0){
		sign = true;
		n *= -1;
	}

	for(; n > 0; n /= 10){
		if(n % 10 == 0){
			leadZero++;

		}
		else{
			break;
		}
	}

	for(; n > 0; n /= 10){
		res = res * 10 + n % 10;
	}

	while(leadZero > 0){
		std::cout << "0";
		leadZero--;
	}

	if(sign){
		res *= -1;
	}

	std::cout << res << std::endl;

	exit(EXIT_SUCCESS);
}