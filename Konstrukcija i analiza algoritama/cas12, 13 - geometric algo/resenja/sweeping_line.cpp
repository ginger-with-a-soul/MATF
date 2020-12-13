#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// Forward deklaracija zbog using
class Point;
// Duzi posmatramo kao parove tacaka
using Segment = std::pair<Point, Point>;

class Point
{
public:
  // Defautl-ni konstruktor
  Point () {}

  // Konstruktor koji pima koordinate tacke i informaciju da li je ona pocetna ili krajanja tacka neke duzi
  Point (int _x, int _y, bool start)
  {
    x = _x;
    y = _y;
    is_start_point = start;
  }

  // Copy konstruktor
  Point (const Point &p)
  {
    this->x = p.x;
    this->y = p.y;
    this->is_start_point = p.is_start_point;
  }

  // Getteri
  int get_x() const { return x; }
  int get_y() const { return y; }
  bool get_is_start_point() const { return is_start_point; }

  // Setteri
  void set_x(int x) { this->x = x; }
  void set_y(int y) { this->y = y; }

  // Operator za poredjenje 2 tacke
  bool operator==(const Point &p) const { return this->x == p.x && this->y == p.y; }

private:
  // x koordinata tacke
  int x;
  // y koordinata tacke
  int y;
  // Cuvamo informaciju da li je tacka pocetna ili krajnja tacka neke duzi, kako bismo znali koji dogadjaj obradjujemo, tome sluzi ova promenljiva
  bool is_start_point;
};

// Funkcijski objekat koji odredjuje poredak duzi u statusu. Sve duzi su sortirane rastuce po vrednosti y koordinate. Tako da ako naidjemo na
// vise duzi koje imaju istu vrednost x koordinate nekog temena onda ih obradjujemo odozdo nagore
class comparator
{
public:
  bool operator()(const Segment &s_1, const Segment &s_2)
  {
    return s_1.first.get_y() < s_2.first.get_y();
  }
};

// Funkcijski objekat koji odredjuje poredak dogadjaja koji se obradjuju. Svi dogadjaji su sortirani rastuce po vrednosti x koordinate pocetnog temena
class comparator_events
{
public:
  bool operator()(const Segment &s_1, const Segment &s_2)
  {
    // Ako se poklapaju x koordinate pocetnih tacaka duzi
    if (s_1.first.get_x() == s_2.first.get_x()) {
      // Zelimo duz ciju krajnju tacku razmatramo da stavimo u poretku posle druge duzi. Ako imamo pretpostavku da duzi ne dele temena,
      // ovakav slucaj imamo samo ako imamo kraj horizontalne duzi i vertikalnu duz koja prolazi kroz nju (u primeru sa slike duzi CD i UT)
      // Zelimo da horizontalna duz bude nakon vertikalne da bismo prvo obradili dogadjaj vertikalne duzi i otkrili presek pre nego sto izbacimo
      // horizontalnu duz iz statusa
      if (!s_1.first.get_is_start_point())
        return false;
      if (!s_2.first.get_is_start_point())
        return true;

      // Ako su oba temena pocetna (na slici duzi MW i KV) onda hocemo da ih obradimo rastuce po y koordinati, tj prvo horizontalnu (ubacujemo je u status)
      // a onda vertikalnu (otkrivanje preseka)
      // Ovim pokrivamo i kada imamo 2 horizontalne duzi koje se zavrsavaju, tu poredak nije bitan, bitno je samo da obe budu nakon vertikalne duzi
      return s_1.first.get_y() < s_2.first.get_y();
    }

    return s_1.first.get_x() < s_2.first.get_x();
  }
};

// Provera da li je duz horizontanla
bool is_horizontal(const Segment &s)
{
    // Ako i pocetna i krajnja tacka imaju vrednost y koordinate koja je jednaka onda je ta duz horizontanla
    return s.first.get_y() == s.second.get_y();
}

// Overload-ovanje operatora za ispisivanje. U C++-u mozemo da overload-ujemo operatore za ispisivanje u neki stream (standardni izlaz u ovom slucaju)
// i da definisemo u kom formatu zelimo da se neki objekat ispise, tako i ovde definisemo na koji nacin zelimo da se ispisuju duzi
std::ostream &operator<<(std::ostream &out, const Segment &s)
{
  // std::cout << "{ [" << s.first.get_x() << ", " << s.first.get_y() << "], ["<< s.second.get_x() << ", " << s.second.get_y() << "] } -> " << (is_horizontal(s) ? "Horizontal" : "Vertical") << std::endl;

  std::cout << "{ [" << s.first.get_x() << ", " << s.first.get_y() << "], ["<< s.second.get_x() << ", " << s.second.get_y() << "] }";

  return out;
}

// Funkcija poredjenja koja sluzi za pronalazenje "najnize" duzi koju sece neka vetrikalna duz
bool compare_lower(const Segment &s_1, const Segment &s_2)
{
  return s_1.first.get_y() < s_2.second.get_y();
}

// Funkcija poredjenja koja sluzi za pronalazenje "najnize" duzi iznad "najvise" duzi koju sece neka vetrikalna duz
bool compare_upper(const Segment &s_1, const Segment &s_2)
{
  return s_1.first.get_y() < s_2.first.get_y();
}

void find_intersections(std::vector<Segment> segments)
{
  // Status je skup koji cuva sve duzi koje u tom trenutku sece brisuca prava, one su samo horizontalne, a kad se naidje na vertikalnu, onda
  // se prolazi kroz status da se vidi koje duzi ona sece. Njihov poredak je odredjen funkcijskim objektom comparator
  std::set<Segment, comparator> status;

  // Events je multiskup duzi koji predstavlja dogadjaje koji se obradjuju. Poredak je odredjen funkcijskim objektom comparator_events
  // Potrebno nam je uredjenje i efikasno ubacivanje i izbacivanje pa se zato ne koristi std::vector
  std::multiset<Segment, comparator_events> events;

  // Prolazimo kroz sve duzi
  for (const Segment &s : segments) {
    // Svaku od duzi ubacujemo u dogadjaje
    events.insert(s);

    // Ako je duz bila horizontalna onda cemo ubaciti i njoj odgovarajucu obrnutu duz. Ako smo imali duz AB ubacujemo i BA.
    // Ovo radimo jer zelimo da obradimo i dogadjaj "izlaska" iz duzi, a da bismo mogli da celu duz nadjemo i izbacimo iz skupa dogadjaja moramo da imamo
    // kompletnu informaciju o njoj, i pocetnu i krajnju tacku. Pri izbacivanju duzi iz skupa dogadjaja cemo traziti duz s.second, s.first, jer smo ovde
    // umesto duzi AB ubacili duz BA, kada budemo trazili odgovarajucu duz u skupu dogadjaja trebace nam AB
    // Ako bismo ubacili samo duz AB kako da detektujemo kraj duzi?
    if (is_horizontal(s)) {
      events.insert({s.second, s.first});
    }
  }

  // Prolazimo kroz sve dogadjaje redom
  for (const Segment &event : events) {
    // std::cout << "Event:\n";
    //
    // std::cout << event << "\n";

    // Ako imamo horizontalnu duz ili je treba dodati u status ili izbaciti iz istog
    if (is_horizontal(event)) {
      // Ako smo naisli na "ulaznu" tacku duzi treba duz event dodati u status
      if (event.first.get_is_start_point())
        status.insert(event);
      // Ako smo naisli na "izlaznu" tacku duzi onda njoj obrnutu duz treba izbaciti iz statusa. Ako imamo u statusu duz AB ovde bismo naisli na duz BA
      // sto znaci da treba uzeti event.second (A) i event.first(B) i bas tu duz (AB) izbaciti iz statusa
      else {
        Segment tmp {event.second, event.first};
        status.erase(std::find(status.begin(), status.end(), tmp));
      }
    }
    // Ako je u pitanju vertikalna duz treba naci sve duzi sa kojima ona ima presek
    else {
      // std::cout << "Status:\n";
      // for (Segment seg : status)
      //   std::cout << seg << "\n";

      // Nalazimo prvu duz u statusu (u njemu su sve duzi horizontalne) za koju vazi da joj je y koordinata >= y koordinati donjeg temena trenutne duzi koja
      // se gleda
      auto lower = std::lower_bound(status.begin(), status.end(), event, compare_lower);

      // Ako sigurno nema nijedne duzi koju sece trenutna duz idemo dalje samo
      // Jedan uslov je da smo dosli do status.end() (duz A1Z sa slike, iznad nje nema nicega pa dobijamo status.end())
      // Drugi uslov odgovara duzi B1C1 sa slike, jer je njeno gornje teme ispod svih horizontalnih duzi
      if (lower == status.end() || lower->first.get_y() > event.first.get_y())
        continue;

      // Nalazimo prvu duz u statusu (u njemu su sve duzi horizontalne) za koju vazi da joj je y koordinata < y koordinate gornjeg temena trenutne duzi
      // koja se gleda
      auto upper = std::upper_bound(status.begin(), status.end(), event, compare_upper);
      // Vracamo se za jednu poziciju nazad u odnosu na nadjenu duz, jer moze da se desi da smo dosli do status.end(), tj poslednja duz iz statusa je trazena
      // i trazimo prvu za koju vazi da je y > event.first.y pa vracanjem dolazimo bas do duzi koja nam treba
      upper--;

      // std::cout << "lower: " << *lower;
      // std::cout << "upper: " << *upper;

      auto begin = lower;
      // Prolazimo kroz sve duzi koje sece nasa duz i ispisujemo preseke
      for (; begin != upper; begin++)
        std::cout << "Segments " << event << " and " << *begin << " intersects at point (" << event.first.get_x() << ", " << (*begin).first.get_y() << ")\n";

      // Ako smo imali samo jednu duz npr, necemo imati nijednu iteraciju prethodne petlje pa treba ispisati odgovarajuci presek
      if (begin == upper && begin != status.end())
        std::cout << "Segments " << event << " and " << *begin << " intersects at point (" << event.first.get_x() << ", " << (*begin).first.get_y() << ")\n";
    }
  }
}

int main ()
{
  std::vector<Segment> segments = { {{1, 2, true}, {3, 2, false}}, {{4, 6, true}, {4, -5, false}}, {{1, 1, true}, {8, 1, false}},
                                    {{2, 3, true}, {2, -2, false}}, {{6, 2, true}, {6, 0, false}}, {{2, 4, true}, {6, 4, false}},
                                    {{-2, -1, true}, {5, -1, false}}, {{5, 4, true}, {5, 1, false}}, {{7, 6, true}, {7, 2, false}},
                                    {{8, 2, true}, {8, -2, false}}, {{-2, 2, true}, {-2, -2, false}}, {{2, 8, true}, {2, 6, false}},
                                    {{5, -2, true}, {5, -4, false}}, {{-2, 1, true}, {0, 1, false}}, {{6, -1, true}, {8, -1, false}} };

  find_intersections (segments);

  return 0;
}
