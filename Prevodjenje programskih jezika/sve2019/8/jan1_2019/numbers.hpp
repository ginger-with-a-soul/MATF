#ifndef __NUMBERS_HPP__
#define __NUMBERS_HPP__

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

class Broj {
	private:
		std::vector<int> _b;
	public:
		Broj() {};
		Broj(const Broj& b2);
		Broj(int x);
		Broj(const std::vector<int>& v);

		void show(std::ostream& out) const;
		void show(int base) const;

		int get_size() const;
		void push_back(int x);

		int operator[](int i);
		
		bool operator==(const Broj& b1) const;
		bool operator!=(const Broj& b1) const;

		Broj* operator+(const Broj& b1) const;
		Broj* operator-() const;
		Broj* operator-(const Broj& b1) const;
		Broj* operator*(const Broj& b1) const;
		Broj* operator/(const Broj& b1) const;

		Broj* operator&(const Broj& b1) const;
		Broj* operator|(const Broj& b1) const;
		Broj* operator^(const Broj& b1) const;
		Broj* operator~() const;
		Broj* operator<<(const Broj& b1) const;
		Broj* operator>>(const Broj& b1) const;


};

std::ostream& operator<<(std::ostream& out, const Broj& b);

#endif