import os
import re
import sys


def get_name_dict(base_dir):
    """
    Funkcija vraca preslikavanje indeksa studenta (na primer 'mi13111')
    u njegovo ime i prezime.
    Podaci se formiraju na osnovu putanje './base_dir/indeksi.txt'.
    """
    imena = {}

    with open(os.path.join(base_dir, 'indeksi.txt'), 'r') as f:
        for linija in f:
            tokeni = linija.split(",")
            if len(tokeni) >= 2:
                indeks = tokeni[0].strip()
                ime = tokeni[1].strip()
                imena[indeks] = ime
            else:
                print('Preskacemo liniju, podaci nisu validni...')
    return imena


def main():
    if len(sys.argv) != 2:
        sys.exit('Molimo da prosledite datoteku kao argument komandne linije.')

    # ekstenzije = ['cpp', 'py', 'elm', 'lisp', 'cobol', 'c', 'js', 'php', 'fortran']
    # Umesto liste, bolje je koristiti Python strukturu za skup podataka.
    # Kako se skupovi cesto implementiraju preko stabala, operacija provere pripadnosti
    # ekstenzije bi asimptotski trebala da bude brza nego kod liste (gde bi bila linearna pretraga).
    ekstenzije = set(['cpp', 'py', 'elm', 'lisp', 'cobol', 'c', 'js', 'php', 'fortran'])

    base_dir = sys.argv[1]
    name_map = get_name_dict(base_dir)
    print('Dostupni studenti:')
    for i, name in name_map.items():
        print(i, '->', name)

    # Izlistavamo base_dir.
    dirs = os.listdir(base_dir)

    studenti = {}

    indeks_re = re.compile('m[mnvlria]{1,2}\d{5}')
    # Prolazimo kroz direktorijume...
    for ime_dir in dirs:
        if indeks_re.match(ime_dir):
            # Ukoliko je ime direktorijuma u obliku koji predstavlja
            # validni studentski indeks na Matematickom fakultetu...
            studenti[ime_dir] = {}

            # Izlistavamo projekte studenta...
            datoteke = os.listdir(os.path.join(base_dir, ime_dir))
            # print(datoteke)

            # Iteriramo kroz projekte studenta
            for datoteka in datoteke:
                # Uzimamo ekstenziju imena datoteke
                ext = datoteka.split(".")[-1]
                # Ako je ekstenzija u skupu validnih ekstenzija...
                if ext in ekstenzije:
                    if ext in studenti[ime_dir]:
                        studenti[ime_dir][ext] += 1
                    else:
                        studenti[ime_dir][ext] = 1

    # Ispisujemo podatke - domaci: formatirajte lepo tabelu
    print('\nPregled aktivnosti studenata tokom leta:')
    for indeks, podaci_studenta in studenti.items():
        print(indeks, podaci_studenta)


if __name__ == "__main__":
    main()
