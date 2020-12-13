#include "broj.hpp"

using namespace std;

extern void yyerror(string s);

Broj::Broj(int x) {
	
	_b.push_back(x);
}

Broj::Broj(const vector<int>& v) {
	_b = v;
}

Broj::Broj(const Broj& b) {
	
	_b = b._b;
}

void Broj::show(ostream& s) const {
	
	if (_b.size() > 1) {
		s<<'[';
		for (auto it = _b.begin(); it != _b.end(); it++) {
			if (it != _b.begin())
				s<<", ";
			s<<*it;
		}
		s<<']';
	}
	else {
		
		s << _b[0];
	}
	s<<endl;
}
void Broj::show(int base) const {
	
	if (_b.size() > 1) {
		
		cout<<'[';
		for (auto it = _b.begin(); it != _b.end(); it++) {
			
			if (it != _b.begin())
				cout<<", ";
			switch(base){
				case 8:
					printf("0%o\n", *it);
					break;
				case 16:
					printf("0x%x\n", *it);
					break;
				default:
					yyerror("Nepodrzana osnova\n");
					break;
			}
		}
	}
	else {
		
		switch(base){
				case 8:
					printf("0%o\n", _b[0]);
					break;
				case 16:
					printf("0x%x\n", _b[0]);
					break;
				default:
					yyerror("Nepodrzana osnova\n");
					break;
			}
	}
}

int Broj::get_size() const {
	
	return _b.size();
}
void Broj::push_back(int x) {
	
	_b.push_back(x);
}

int Broj::operator [](int i) {
	
	return _b[i];
}

bool Broj::operator ==(const Broj& b) const {
	
	if (_b.size() != b._b.size())
		return false;
	
	for (int i = 0; i < _b.size(); i++) {
		
		if (_b[i] != b._b[i])
			return false;
	}
	
	return true;
}

bool Broj::operator != (const Broj& b) const {
	
	if (_b.size() != b._b.size())
		return true;
	
	for (int i = 0; i < _b.size(); i++) {
		
		if (_b[i] != b._b[i])
			return true;
	}
	
	return false;
}

Broj* Broj::operator +(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(_b[i] + b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator -(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(_b[i] - b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator *(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(_b[i] * b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator /(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(_b[i] / b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator %(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(_b[i] * b._b[i]);
	}
	
	return noviBroj;
}

Broj* Broj::operator &(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(_b[i] & b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator |(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(_b[i] | b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator ^(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(_b[i] ^ b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator <<(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		if (b._b[i] < 0) {
			yyerror("Negativan broj");
		}
		noviBroj->push_back(_b[i] << b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator >>(const Broj& b) const {
	
	if (_b.size() != b._b.size()){
		yyerror("Neodgovarajuce dimenzije");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		if (b._b[i] < 0) {
			yyerror("Negativan broj");
		}
		noviBroj->push_back(_b[i] >> b._b[i]);
	}
	
	return noviBroj;
}

Broj* Broj::operator -() const {
	
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(-_b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator ~() const {
	
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		noviBroj->push_back(~_b[i]);
	}
	
	return noviBroj;
}

ostream& operator <<(ostream& s, const Broj& b) {
	
	b.show(s);
	return s;
}
