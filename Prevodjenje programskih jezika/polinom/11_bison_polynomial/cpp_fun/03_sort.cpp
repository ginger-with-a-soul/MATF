#include <iostream>
#include <algorithm>
#include <vector>

class student {
public:
    student(const std::string& s)
        : m_name(s)
    {}

    const std::string& name() const { return m_name; }

    bool operator<(const student& s) const
    {
        return m_name < s.m_name;
    }

private:   
    std::string m_name; 
};

bool comparator_descending(int a, int b)
{
    return a > b;
}

int main()
{
    std::vector<int> xs{4, 1, 2, 3, -100, 6};

    auto comparator_ascending = [] (int a, int b) {
        return a < b;
    };

    std::sort(xs.begin(), xs.end(), comparator_ascending);
    for (auto e:  xs) std::cout << e << " ";
    std::cout << std::endl;

    std::sort(xs.begin(), xs.end(), comparator_descending);
    for (auto e:  xs) std::cout << e << " ";
    std::cout << std::endl;

    // Elegantiji nacin je direktno pisanje lambda funkcije
    // pri pozivu za sortiranje. Usput se moze koristiti auto
    // da se izbegne pisanje tipova.
    std::sort(xs.begin(), xs.end(), [] (auto a, auto b) { return a < b; });
    for (auto e:  xs) std::cout << e << " ";
    std::cout << std::endl;

    std::vector<student> studenti {
        student("Stefan"),
        student("Matija"),
        student("Olivera"),
        student("Aleksandra"),
        student("Aleksandar"),
        student("Konstantin")
    };

    // Posto smo implementirali operator < ne moramo da prosledjujemo
    // komparator vec ce funkcija koristiti nasu implementaciju za sortiranje;
    std::sort(studenti.begin(), studenti.end());
    for (auto s : studenti) {
        std::cout << "- " << s.name() << std::endl;
    }

    return 0;
}
