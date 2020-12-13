#include "skup.hpp"

using namespace std;

Skup::Skup(int begin, int end) {
	
	for (int i = begin; i <= end; i++) {
		
		_elementi.insert(i);
	}
}

Skup::Skup(const set<int>& elementi) {
	
	_elementi = elementi;
}

Skup::Skup(const Skup& s) {
	
	_elementi = s._elementi;
}

void Skup::show(ostream& s) const {
	
	s<<"{";
	for (auto it = _elementi.begin(); it != _elementi.end(); it++) {
		if (it != _elementi.begin())
			s<<", ";
		s<<*it;
	}
	
	s<<"}";
}

Skup* Skup::operator +(const Skup& s) const {
	
	Skup* noviSkup = new Skup(s);
	
	for (auto it = _elementi.begin(); it != _elementi.end(); it++) {
		
		noviSkup->insert(*it);
	}
	
	return noviSkup;
}

Skup* Skup::operator -(const Skup& s) const {
	
	Skup* noviSkup = new Skup();
	
	for (auto it = _elementi.begin(); it != _elementi.end(); it++) {
		
		if (!(s.find(*it))) {
			noviSkup->insert(*it);
		}
	}
	
	return noviSkup;
}

Skup* Skup::operator *(const Skup& s) const {
	
	Skup* noviSkup = new Skup();
	
	for (auto it = _elementi.begin(); it != _elementi.end(); it++) {
		
		if (s.find(*it)) {
			noviSkup->insert(*it);
		}
	}
	
	return noviSkup;
}

Skup* Skup::komplement(const Skup& s) const {
	
	Skup* noviSkup = new Skup();
	
	for (auto it = _elementi.begin(); it != _elementi.end(); it++) {
		
		if (!(s.find(*it))) {
			noviSkup->insert(*it);
		}
	}
	
	return noviSkup;
}

bool Skup::find(int x) const {
	
	return _elementi.find(x) != _elementi.end();
}

bool Skup::subset(const Skup& s) const {
	
	for (auto it = s._elementi.begin(); it != s._elementi.end(); it++) {
		
		if (!(this->find(*it))) {
			
			return false;
		}
	}
	return true;
}

int Skup::card(void) const {
	
	return _elementi.size();
}

void Skup::insert(int x) {
	
	_elementi.insert(x);
}


ostream& operator <<(ostream& s, const Skup& ss) {
	
	ss.show(s);
	return s;
}
