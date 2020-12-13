#ifndef ppj_POLINOMIAL_HPP
#define ppj_POLINOMIAL_HPP

#include <vector>
#include <iostream>

class polinomial {
public:
    polinomial();
    polinomial(const std::vector<float>& coefs);

    // GETeri
    const std::vector<float>& coefs() const;
    unsigned power() const;

    // Prvi nacin - implementacija operatora za sabiranje
    // kao funkcije clanice (member function, method) koja sabira objekte *this i p.
    polinomial operator+(const polinomial& p) const;
    
    // Drugi nacin, i cesci za binarne operatore kako bi argumenti bili simetricni,
    // odnosno a i b, ili lhs i rhs umesto this (pokazivac) i p (referenca).
    // Ovde se funkcije deklarisu kao prijateljske funkcije za klasu kako bi mogle
    // da pristupe privatnim podacima. OVO NARUSAVA ENKAPSULACIJU, ali je cesto
    // u praksi usled dobijanja na performansama.
    friend polinomial operator-(const polinomial& a, const polinomial& b);
    friend polinomial operator*(const polinomial& a, const polinomial& b);

    // Alternativa (treci nacin) definisanju operatora bi bila implementacija
    // funkcija clanica (member function, method) koji implementiraju slicnu logiku.
    // Na primer:
    // polinomial add(const polinomial& p) const;
    // polinomial sub(const polinomial& p) const;
    // polinomial mul(const polinomial& p) const;

private:
    std::vector<float> m_coef;

    // Kako bi omogucili lep ispis nase klase potrebno je da definisemo kako se
    // polinom ispisuje na tok (std::ostream).
    // Kako bi izbegli pozivanje GETera, opet deklarisemo funkciju kao prijateljsku
    // kako bi direktno citali privatne vrednosti.
    friend std::ostream& operator<<(std::ostream& out, const polinomial& p);
};

#endif
