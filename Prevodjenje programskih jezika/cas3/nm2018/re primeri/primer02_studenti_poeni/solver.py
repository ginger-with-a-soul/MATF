import re
import sys

"""
Napisati skript koji rezultate sa ispita iz datoteke 'rezultati_ispita.html' ispisuje
na standardni izlaz, sortirano po ukupnom broju poena neopadajuce.
Poeni sa pismenog se skaliraju sa intervala
[0, 100] na interval [0, 60], a poeni sa usmenog sa intervala [0, 100] na interval [0, 40].
Njihov zbir daje ukupan broj poena.

U datoteci 'rezultati_ispita.html' podaci su zadati tablerarno tako da:
    - kolona 0 oznacava ime studenta
    - kolona 1 oznacava poene sa pismenog ispita iz intervala [0, 100]
    - kolona 2 oznacava poene sa usmenog ispita iz intervala [0, 100]
"""

def main():
    if len(sys.argv) != 2:
        sys.exit('Molimo dajte ulaznu datoteku...')

    input_path = sys.argv[1]
    if not re.search('[.]html$', input_path):
    # if not input_path.endswith('.html'):
        sys.exit('Ekstenzija datoteke mora biti html...')


    with open("rezultati_ispita.html", 'r') as f:
        data = f.read()

    re_regex = r"""
    <td>\s*(?P<ime>[a-zA-Z]+\s+[a-zA-Z]+)\s*</td>\s*        # VERBOSE mode dozvoljava pisanje komentara
    <td>\s*(?P<pismeni>\d+)\s*</td>\s*                      # don't worry
    <td>\s*(?P<usmeni>\d+)\s*</td>                          # be happy :D
    """

    # Rezultat poziva funkcije je regex objekct koji predstavlja prevedni
    # regularni izraz. Funkciju compile treba koristiti u situacijama kada
    # je neophodno vise puta vrsiti proveru pripadnosti reci regularnom jeziku
    # koji regularni izraz definise.
    re_compiled = re.compile(re_regex, re.VERBOSE)

    studenti = []
    # Iteriramo kroz sve podatke koji zadoljavaju regex:
    for x in re_compiled.finditer(data):
        pismeni = float(x.group('pismeni'))
        pismeni = pismeni/100 * 60.0
        usmeni = float(x.group('usmeni'))
        usmeni = usmeni/100 * 40.0
        studenti.append({
            'ime': x.group('ime'),
            'pismeni': pismeni,
            'usmeni': usmeni,
            'ukupno': pismeni + usmeni
        })

    # for student in studenti:
        # print(student['ime'], student['pismeni'], student['usmeni'], student['ukupno'])

    # Funkcija se moze i lokalno definisati, nece biti vidljiva izvan
    # tekuceg opsega - u nasem slucaju funkcije main.
    def poredjenje(student):
        return student['ukupno']

    # Nacini za sortiranje:
    studenti.sort(key=poredjenje, reverse=True)
    # studenti.sort(key=lambda x: x['ukupno'], reverse=True)
    # studenti.sort(reverse=True, key=poredjenje)

    for i, student in enumerate(studenti):
        print(i+1, student['ime'], student['ukupno'])

if __name__ == "__main__":
    main()
