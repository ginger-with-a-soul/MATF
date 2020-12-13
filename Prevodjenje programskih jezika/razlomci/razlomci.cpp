#include <iostream>
#include <functional>
#include "razlomci.hpp"

int nzd(int a, int b) { 
    // lambda za racunanje euklidovog algoritma
    const static std::function<int(int,int)> euklid = [](int a, int b) {
        if (b == 0) 
            return a;
        else
            return euklid(b, a % b);
    };

    if (a == 0 || b == 0)
        return 1;
    else
        return a >= b ? euklid(a, b) : euklid(b, a); 
}

Razlomak::Razlomak() : Razlomak(0){}

Razlomak::Razlomak(int brojilac) : brojilac(brojilac){
	this->brojilac = brojilac;
	this->imenilac = 1;
	this->skrati();
}

Razlomak::Razlomak(int brojilac, int imenilac) : brojilac(brojilac), imenilac(imenilac){
	if(brojilac == 0 && imenilac == 0){
		throw std::string("Nije dozvoljeno pravljenje razlomka 0/0!");
		*this = Razlomak();
	}
	else{
		this->skrati();
	}
}

Razlomak::Razlomak(const Razlomak& rc){
	this->brojilac = rc.brojilac;
	this->imenilac = rc.imenilac;
	this->skrati();
}

Razlomak operator+(const Razlomak& r1, const Razlomak& r2){
	Razlomak rez;
	rez.brojilac = r1.brojilac * r2.imenilac + r2.brojilac * r1.imenilac;
	rez.imenilac = r1.imenilac * r2.imenilac;
	return rez.skrati();
}

Razlomak operator-(const Razlomak& r1){
	Razlomak rez;
	rez.brojilac = -r1.brojilac;
	return rez.skrati();
}

Razlomak operator-(const Razlomak& r1, const Razlomak& r2){
	Razlomak rez;
	rez.brojilac = r1.brojilac * r2.imenilac - r2.brojilac * r1.imenilac;
	rez.imenilac = r1.imenilac * r2.imenilac;
	return rez.skrati();
}

Razlomak operator*(const Razlomak& r1, const Razlomak& r2){
	Razlomak rez;
	rez.brojilac = r1.brojilac * r2.brojilac;
	rez.imenilac = r1.imenilac * r2.imenilac;
	return rez.skrati();
}

Razlomak operator/(const Razlomak& r1, const Razlomak& r2){
	if(r2.imenilac == 0 || r2.brojilac == 0){
		throw std::string("Deljenje nulom nije dozvoljeno!");
		return Razlomak();
	}
	Razlomak rez;
	rez.brojilac = r1.brojilac * r2.imenilac;
	rez.imenilac = r1.imenilac * r2.brojilac;
	return rez.skrati();
}

std::ostream& operator<<(std::ostream& out, const Razlomak& r){
	if(r.imenilac == 1){
		out << '[' << r.brojilac << ']';
	}
	else{
		out << '[' << r.brojilac << ", " << r.imenilac << ']';
	}

	return out;
}

Razlomak::operator double(){
	return (double) this->brojilac / (double) this->imenilac;
}

bool operator==(const Razlomak& r1, const Razlomak& r2){
	if(r1.imenilac == r2.imenilac && r1.brojilac == r2.brojilac){
		return true;
	}
	else{
		return false;
	}
}

Razlomak& Razlomak::skrati() { 

    if (brojilac < 0 && imenilac < 0) {
        brojilac = abs(brojilac);
        imenilac = abs(imenilac);
    } else if (imenilac < 0 && brojilac >= 0) {
        brojilac = -brojilac;
        imenilac = abs(imenilac);
    }

    // :: kaze da referisemo na f-ju a ne na promenljivu nzd
    int nzd = ::nzd(abs(brojilac), abs(imenilac));

    // Skracivanje sa nzd
    imenilac /= nzd;
    brojilac /= nzd;

    return *this;
}