#ifndef POLINOM_H
#define POLINOM_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class Polinom {
	
	private:
		vector<double> _coeffs;
	public:
		Polinom() {}
		Polinom(int deg);
		Polinom(const vector<double>& elementi);
		Polinom(const Polinom& p);
		
		void insert(double x);
		void normalizuj();
		
		Polinom* operator +(const Polinom& p) const;
		Polinom* operator -(const Polinom& p) const;
		Polinom* operator *(const Polinom& p) const;
		
		Polinom* operator -() const;
		
		bool operator ==(const Polinom& p) const;
		bool operator !=(const Polinom& p) const;
		
		//double operator [](double x) const;
		double valueAt(double x) const;
		
		Polinom* izvod() const;
		Polinom* integral(double c) const;
		
		void show(ostream& s) const;
};

ostream& operator <<(ostream& s, const Polinom& p);

#endif
