#include <iostream>
#include <map>
#include <string>

int main()
{
    // Mapa sadrzi informacije o tome u koliko se video igara (vrednost mape)
    // pojavio sa sa imenom koje predstavlja kljuc u mapi.
    std::map<std::string, unsigned> ucesce_u_igrama;

    // Prvi nacin da se doda u mapu - koristeci operator []
    ucesce_u_igrama["Geralt of Rivia"] = 3;

    // Drugi nacin (insert) ali koristeci std::make_pair
    ucesce_u_igrama.insert(std::make_pair("Marcus Holloway", 1));

    // Treci nacin (insert) ali koristeci konstruktor za uredjeni par
    ucesce_u_igrama.insert(std::pair<std::string, unsigned>("Ezio Auditore da Firenze", 3));

    // Pretraga mape
    std::string name = "Geralt of Rivia";
    auto finder = ucesce_u_igrama.find(name);
    if (finder != ucesce_u_igrama.end()) {
        std::cout << finder->first << " broj igara: " << finder->second << std::endl;
    } else {
        std::cout << finder->first << " nije ucestvovao..." << std::endl;
    }

    // Obilazak mape - prvi nacin
    for (auto i = ucesce_u_igrama.cbegin(); i != ucesce_u_igrama.cend(); i++) {
        std::cout << i->first << ": " << i->second << std::endl;
    }

    // Obilazak mape - drugi nacin
    for (const auto& i: ucesce_u_igrama) {
        std::cout << i.first << ": " << i.second << std::endl;
    }

    // Operator[] se moze koristiti i za citanje
    std::cout << name << " broj igara: " << ucesce_u_igrama[name] << std::endl;
    // Ali sta se desava ako se cita nesto sto ne postoji?
    unsigned tmp = ucesce_u_igrama["Duke Nukem"];
    std::cout << tmp << std::endl;
    // Stavise, pogledajmo sada sadrzaj mape i primeticemo
    // da je dodat novi cvor (Duke Nukem, 0) sto mozda i nismo hteli...
    for (const auto& i: ucesce_u_igrama) {
        std::cout << i.first << ": " << i.second << std::endl;
    }

    return 0;
}
