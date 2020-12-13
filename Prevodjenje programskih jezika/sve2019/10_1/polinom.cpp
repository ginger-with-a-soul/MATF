#include "polinom.hpp"

using namespace std;

Polinom::Polinom(int deg) {
	
	_coeffs.resize(deg);
	for (auto it = _coeffs.begin(); it != _coeffs.end(); it++) {
		*it = 0;
	}
}
Polinom::Polinom(const vector<double>& elementi) {
		
	_coeffs = elementi;
}

Polinom::Polinom(const Polinom& p) {
	
	_coeffs = p._coeffs;
}

void Polinom::insert(double x) {
	
	_coeffs.push_back(x);
}
void Polinom::normalizuj() {
	
	for (auto it = _coeffs.rbegin(); it != _coeffs.rend() && *it == 0; it++) {
		
		_coeffs.pop_back();
	}
}

Polinom* Polinom::operator +(const Polinom& p) const {
		
	Polinom* newPoly = new Polinom();
	
	auto it1 = _coeffs.begin();
	auto it2 = p._coeffs.begin();
	
	for (;it1 != _coeffs.end() && it2 != p._coeffs.end(); it1++, it2++) {
		newPoly->insert(*it1 + *it2);
	}
	
	for (; it1 != _coeffs.end(); it1++)
		newPoly->insert(*it1);
	for (; it2 != p._coeffs.end(); it2++)
		newPoly->insert(*it2);
	
	newPoly->normalizuj();
	
	return newPoly;
}

Polinom* Polinom::operator -(const Polinom& p) const {
	
	Polinom* newPoly = new Polinom();
	
	auto it1 = _coeffs.begin();
	auto it2 = p._coeffs.begin();
	
	for (;it1 != _coeffs.end() && it2 != p._coeffs.end(); it1++, it2++) {
		newPoly->insert(*it1 - *it2);
	}
	
	for (; it1 != _coeffs.end(); it1++)
		newPoly->insert(*it1);
	for (; it2 != p._coeffs.end(); it2++)
		newPoly->insert(-(*it2));
	
	newPoly->normalizuj();
	
	return newPoly;
}
Polinom* Polinom::operator *(const Polinom& p) const {
	
	int deg1 = _coeffs.size();
	int deg2 = _coeffs.size();
	
	Polinom* newPoly = new Polinom(deg1 + deg2);
	
	for (int i = 0; i < deg1; i++) {
		for (int j = 0; j < deg2; j++) {
			newPoly->_coeffs[i+j] += _coeffs[i]*p._coeffs[j];
		}
	}
	
	newPoly->normalizuj();
	
	return newPoly;
}

Polinom* Polinom::operator -() const {
	
	Polinom* newPoly = new Polinom();
	
	for (auto it = _coeffs.begin(); it != _coeffs.end(); it++) {
		newPoly->insert(*it);
	}
	
	return newPoly;
}

bool Polinom::operator ==(const Polinom& p) const {
	
	return (_coeffs == p._coeffs);
}
bool Polinom::operator !=(const Polinom& p) const {
	
	return !(_coeffs == p._coeffs);
}

double Polinom::valueAt(double x) const {
	
	auto it = _coeffs.rbegin();
	double result = *it;
	
	for (it++; it != _coeffs.rend(); it++) {
		result += result*x + *it;
	}
	
	return result;
}

Polinom* Polinom::izvod() const {
	
	Polinom* newPoly = new Polinom(_coeffs);
	int deg = newPoly->_coeffs.size();
	
	for (int i = 0; i < deg; i++) {
		
		newPoly->_coeffs[i] *= i;
	}
	
	newPoly->_coeffs.erase(newPoly->_coeffs.begin());
	
	return newPoly;
}

Polinom* Polinom::integral(double c) const {
	
	Polinom* newPoly = new Polinom(_coeffs);
	
	newPoly->_coeffs.insert(newPoly->_coeffs.begin(), c);
	
	int deg = newPoly->_coeffs.size();
	
	for (int i = 0; i < deg; i++) {
		if (i > 0)
			newPoly->_coeffs[i] /= i;
	}
	
	return newPoly;
}

void Polinom::show(ostream& s) const {
	
	for (int i = 0; i < _coeffs.size(); i++) {
		
		if (_coeffs.size() > 0) {
			s << "+";
		}
		if (_coeffs[i] != 0) {
			
			s<<_coeffs[i];
			if (i > 0)
				s<<"x"<<i;
		}
	}
}

ostream& operator <<(ostream& s, const Polinom& p) {
	
	p.show(s);
	return s;
}
