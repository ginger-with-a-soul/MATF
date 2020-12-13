#! /usr/bin/env python

import sys
import os
import re


def funkcija(ulaz):

    imena = {}

    try:
        with open(os.path.join(ulaz, "indeksi.txt"), "r") as f:
            for linija in f:
                tokeni = linija.split(",")
                if len(tokeni) >= 2:
                    ime = tokeni[0].strip()
                    indeks = tokeni[1].strip()
                    imena[indeks] = ime
                else:
                    print("Preskacemo liniju!")
                    continue

        except IOError as e:
            sys.exit(e.message)
    
    return imena


def main():

    if len(sys.argv) != 2:
        sys.exit("Losi argumenti!")
    
    ekstenzije = {"cpp", "c", "py", "elm", "lisp", "cobol", "php", "fortran", "js"}

    ulaz = sys.argv[1]
    mapa_imena = funkcija(ulaz)

    direktorijumi = os.listdir(ulaz)

if __name__ == "__main__":
    main()