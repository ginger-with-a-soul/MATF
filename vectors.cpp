#include <iostream>
#include <vector>


int main(){

	std::cout << "Input the size of the vector you want to allocate: ";

	int size;

	std::cin >> size;
	if(size < 1){
		std::cerr << "Invalid value for size..\nTerminating!" << std::endl;
		exit(EXIT_FAILURE); 
	}
	std::vector<int> v1(size);
	//std::vector<int> v;
	//std::vector<int> v({1, 2, 3..});
	//std::vector<int> v(size, 0);
	
	std::cout << "Fill the vector with your desired values: ";
	int x = 0;
 	for(int i = 0; i < size; i++){
		 std::cin >> x;
		 v1[i] = x;
	}

	std::cout << "In reverse order that would be: ";

	auto rbeg = v1.rbegin();
	auto rend = v1.rend();
	for(; rbeg != rend; rbeg++){
		std::cout << *rbeg << " ";
	}
	std::cout << std::endl;

	std::cout << "The first element is: " << v1.front() << "\nAnd the last one is: " << v1.back() << std::endl;

	std::vector<int> v2(v1);

	exit(EXIT_SUCCESS);
}