#include <iostream>
#include <vector>
#include "polinomial.hpp"

int main()
{
    std::vector<float> xs{1, 2, 3, 4};
    polinomial p(xs);
    polinomial q(std::vector<float>{10, 20, 30});
    std::cout << p << std::endl;
    std::cout << q << std::endl;

    std::cout << p + q << std::endl;
    std::cout << p - q << std::endl;
    std::cout << p * q << std::endl;
    return 0;
}

