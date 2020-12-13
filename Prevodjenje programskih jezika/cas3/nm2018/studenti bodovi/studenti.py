#! /usr/bin/env python

import sys
import re

def main():

    if len(sys.argv) != 2:
        sys.exit("Losi argumenti!")
    
    input_path = sys.argv[1]
    if not input_path.endswith(".html"):
        sys.exit("Fajl se mora zavrsavati sa \".html\"")

    try:
        with open(input_path, "r") as f:
            data = f.read();
        
    except IOError as e:
        sys.exit(e.message)

    re_izraz = r"""
                <td>\s*(?P<ime>[A-Z]+[a-z]*\s+[A-Z]+[a-z]*)\s*</td>\s*
                <td>\s*(?P<pismeni>\d{1,3})\s*</td>\s*
                <td>\s*(?P<usmeni>\d{1,3})\s*</td>\s*
                """
    re_izraz_komp = re.compile(re_izraz, re.VERBOSE)

    studenti = []

    for x in re_izraz_komp.finditer(data):
        pismeni = float(x.group("pismeni")) * 0.6
        usmeni = float(x.group("usmeni")) * 0.4
        ukupno = pismeni + usmeni
        studenti.append({
            "Ime i prezime: ": x.group("ime"),
            "Ukupno bodova: ": ukupno,
        })
    
    studenti.sort(key = lambda studenti: studenti["Ukupno bodova: "], reverse = False)

    for (i, student) in enumerate(studenti):
        print(i + 1, student["Ime i prezime: "], student["Ukupno bodova: "])

if __name__ == "__main__":
    main()