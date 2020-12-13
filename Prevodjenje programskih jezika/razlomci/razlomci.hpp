#ifndef __RAZLOMCI_HPP__
#define __RAZLOMCI_HPP__

#include <ostream>

class Razlomak {
public:
    int brojilac,imenilac;
    Razlomak(int brojilac);
    Razlomak(int brojilac, int imenilac);
	Razlomak(const Razlomak& rc);
    Razlomak();
    Razlomak& skrati();

    operator double();
};

Razlomak operator+(const Razlomak& r1, const Razlomak& r2);
Razlomak operator-(const Razlomak& r);
Razlomak operator-(const Razlomak& r1, const Razlomak& r2);
Razlomak operator*(const Razlomak& r1, const Razlomak& r2);
Razlomak operator/(const Razlomak& r1, const Razlomak& r2);
bool operator==(const Razlomak& r1, const Razlomak& r2);
std::ostream& operator<<(std::ostream& out, const Razlomak& r);

#endif