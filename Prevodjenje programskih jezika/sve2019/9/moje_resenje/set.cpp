#ifndef __SET_HPP__
#define __SET_HPP__

#include <iostream>
#include <ostream>
#include <cstdlib>
#include <string>
#include <map>
#include <set>
#include <vector>

class Set {
	private:
		std::set<int> _s;
	public:
		Set();
		Set(std::vector<int>& el);
		Set(const Set& s);

		void show(std::ostream& s);
		Set* operator+(const Set& s2) const;
};

std::ostream& operator<<(std::ostream& s, const Set& set);

Set* Set::operator+(const Set& s2) const {
	Set* new_set = new Set();
}

#endif