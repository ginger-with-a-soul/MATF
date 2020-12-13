#include <iostream>
#include <vector>

void intro_ispis_vektora(std::vector<int>& xs)
{
    // Prvi nacin da se iterira kroz vektor
    for (unsigned i = 0; i < xs.size(); i++)
        std::cout << xs[i] << " ";
    std::cout << std::endl;

    // Drugi nacin (i preporuceni) da se iterira kroz vektor
    // koristeci iteratore.
    for (auto i = xs.cbegin(); i != xs.cend(); i++) {
        // tip od i je std::vector<int>::iterator ali
        // koristeci auto mozemo da izbegnemo njegovo pisanje.
        // cbegin -> const begin
        // cend -> const end
        // Odnosno, ne dozvoljava se menjanje kolekcije kroz
        // dobijeni iterator.
        // Ukoliko zelimo da menjamo mozemo da koristimo
        // begin() i end() (bez c kao prefiks) i da element
        // promenimo sa: *i = 100; na primer.
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    // Treci nacin
    for (int x: xs) std::cout << x << " ";
    std::cout << std::endl;
    // Koristi 'auto' da bi ostavili kompilatoru da zakljuci tip.
    for (auto x: xs) std::cout << x << " ";
    std::cout << std::endl;

    // Ukoliko zelimo da dobijamo direktno elemente
    // iz kolekcije i izbegnemo (potencijalno skupo) kopiranje.
    for (auto& x: xs) {
        x = 100;
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Ukoliko zelimo da dobijamo direktno elemente
    // i zabranimo njihovu modifikaciju u okviru petlje.
    for (const auto& x: xs) std::cout << x << " ";
    std::cout << std::endl;

}

int main()
{
    std::vector<int> xs {1, 2, 3, 4, -1, -2, -3, -4};

    intro_ispis_vektora(xs);

    // Ukoliko zelimo da prealociramo vektor unapred
    // to se moze uciniti na sledeci nacin:
    std::vector<float> ys(3);
    ys[0] = 1.2f;
    ys[1] = 3.2f;
    ys[2] = 1.2f;
    std::cout << "Prealokacija: " << std::endl;
    for (auto& y: ys) std::cout << y << " ";
    std::cout << std::endl;

    // Ukoliko zelimo da inicijalizujemo vektor nekim
    // vrednostima:
    std::cout << "z (inicijalizacija):" << std::endl;
    std::vector<int> zs(4, 0);
    for (auto& z: zs) std::cout << z << " ";
    std::cout << std::endl;

    // Kopiranje vektora (jer je lokalna promenljiva i zivi na steku).
    std::vector<int> zs_copy = zs;

    return 0;
}
