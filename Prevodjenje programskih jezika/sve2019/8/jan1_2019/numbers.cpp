#include "numbers.hpp"
#include <vector>
#include <iostream>

extern void yyerror(std::string errMsg);
using namespace std;

Broj::Broj(int x){
	_b.push_back(x);
}

Broj::Broj(const Broj& b){
	_b = b._b;
}

Broj::Broj(const std::vector<int>& v){
	_b = v;
}

void Broj::show(std::ostream& out) const{
	if(_b.size() > 1){
		out << "[";
		for(auto it = _b.begin(); it != _b.end(); it++){
			if(it != _b.begin()){
				out << ", ";
			}
			out << *it;
		}
		out << "]";
	}
	else{
		out << _b[0];
	}
}

void Broj::show(int base) const {
	if(_b.size() > 1){
		cout << "[";
		for(auto it = _b.begin(); it != _b.end(); it++){
			if(it != _b.begin()){
				cout << ", ";
			}
			else{
				switch(base){
					case 8: printf("0%o\n", *it); break;
					case 16: printf("0x%x\n", *it); break;
					default: yyerror("Nepodrzana osnova"); break;
				}
			}
		}

	}
	else{
		switch(base){
			case 8: printf("0%o\n", _b[0]); break;
			case 16: printf("0x%x\n", _b[0]); break;
			default: yyerror("Nepodrzana osnova"); break;
		}
	}
}

int Broj::get_size() const {
	return _b.size();
}

void Broj::push_back(int x){
	_b.push_back(x);
}

int Broj::operator[](int i){
	return _b[i];
}

bool Broj::operator==(const Broj& b2) const {
	if(b2._b.size() != _b.size()){
		return false;
	}
	else{
		for(int i = 0; i < _b.size(); i++){
			if(_b[i] != b2._b[i]){
				return false;
			}
		}
		return true;
	}
}

bool Broj::operator!=(const Broj& b2) const {
	if(b2._b.size() != _b.size()){
		return true;
	}
	else{
		for(int i = 0; i < _b.size(); i++){
			if(b2._b[i] != _b[i]){
				return true;
			}
		}
		return false;
	}
}

Broj* Broj::operator+(const Broj& b2) const {
	if(b2._b.size() != _b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			b->push_back(b2._b[i] + _b[i]);
		}
		return b;
	}
}

Broj* Broj::operator-(const Broj& b2) const {
	if(_b.size() != b2._b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			b->push_back(_b[i] - b2._b[i]);
		}
		return b;
	}
}

Broj* Broj::operator*(const Broj& b2) const {
	if(_b.size() != b2._b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			b->push_back(_b[i] * b2._b[i]);
		}
		return b;
	}
}

Broj* Broj::operator/(const Broj& b2) const {
	if(_b.size() != b2._b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			if(b2._b[i] == 0){
				yyerror("Deljenje nulom je nedefinisano");
			}
			else{
				b->push_back(_b[i] / b2._b[i]);
			}
		}
		return b;
	}
}

Broj* Broj::operator-() const {
	Broj* b = new Broj();
	for(int i = 0; i < _b.size(); i++){
		b->push_back(-_b[i]);
	}
	return b;
}

Broj* Broj::operator~() const {
	Broj* b = new Broj();
	for(int i = 0; i < _b.size(); i++){
		b->push_back(~_b[i]);
	}
	return b;
}

Broj* Broj::operator&(const Broj& b2) const {
	if(_b.size() != b2._b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			b->push_back(_b[i] & b2._b[i]);
		}
		return b;
	}
}

Broj* Broj::operator|(const Broj& b2) const {
	if(_b.size() != b2._b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			b->push_back(_b[i] | b2._b[i]);
		}
		return b;
	}
}

Broj* Broj::operator^(const Broj& b2) const {
	if(_b.size() != b2._b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			b->push_back(_b[i] ^ b2._b[i]);
		}
		return b;
	}
}

Broj* Broj::operator<<(const Broj& b2) const {
	if(_b.size() != b2._b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			if(b2._b[i] < 0){
				yyerror("Siftovanje ne moze za negativan broj");
			}
			else{
				b->push_back(_b[i] << b2._b[i]);
			}
		}
		return b;
	}
}

Broj* Broj::operator>>(const Broj& b2) const {
	if(_b.size() != b2._b.size()){
		yyerror("Razlicite dimenzije");
	}
	else{
		Broj* b = new Broj();
		for(int i = 0; i < _b.size(); i++){
			if(b2._b[i] < 0){
				yyerror("Siftovanje ne moze za negativan broj");
			}
			else{
				b->push_back(_b[i] >> b2._b[i]);
			}
		}
		return b;
	}
}

std::ostream& operator<<(std::ostream& out, const Broj& b){
	b.show(out);
	return out;
}