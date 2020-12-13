#ifndef SKUP_HPP
#define SKUP_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>

using namespace std;

class Skup {
	
	private:
		set<int> _elementi;
	public:
		Skup() {}
		Skup(int begin, int end);
		Skup(set<int>& elementi);
		Skup(const Skup& s);
		
		void show(ostream& s) const;
		
		Skup* operator +(const Skup& s) const;
		Skup* operator -(const Skup& s) const;
		Skup* operator *(const Skup& s) const;
		
		bool find(int x) const;
		bool subset(const Skup& s) const;
		
		int card(void) const;
		
		void insert(int x);
		
		Skup* complement(Skup& s) const;
};

ostream& operator <<(ostream& s, const Skup& ss);


#endif

