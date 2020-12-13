#! /usr/bin/env python

import re
import sys
import math

def main():

    if len(sys.argv) != 2:
        sys.exit("bad arg count")
    if not sys.argv[1].endswith(".txt"):
        sys.exit("bad file ext")

    try:
        with open(sys.argv[1], "r") as f:
            data = f.read()
    except IOError as e:
        sys.exit(e.message)

    reg = re.compile(r"[0-3][0-9].[01][0-9].[0-9]{2}\t*(?P<alas>m[mnvrli](09|1[0-9])([0-3][0-9][0-9]|400))\t*(?P<ime>[A-Z][a-z]*\s[A-Z][a-z]*[A-Za-z ]*)\t*(?P<klk>([12]?[0-9]|30).[0-9]{2})\t*(?P<teorija>([12]?[0-9]|3[0-5]).[0-9]{2})\t*(?P<prak>([12]?[0-9]|3[0-5]).[0-9]{2})\t*(?P<grupa>(3i|4r|4n))")
    lista = []

    for x in reg.finditer(data):
        klk = float(x.group('klk'))
        teorija = float(x.group('teorija'))
        prak = float(x.group('prak'))
        ukupno = klk + teorija + prak
        if klk >= 0.4*30:
            ocena = math.ceil(ukupno / 10)
        else:
            ocena = 5
        lista.append({
            'ime' : x.group('ime'),
            'alas' : x.group('alas'),
            'ocena' : ocena,
            'bodovi' : ukupno
        })
    
    def komparator(el):
        return el['ocena']

    lista.sort(key=komparator, reverse=True)

    for el in lista:
        print("%s %s %i (%i)" % (el['ime'], el['alas'], el['ocena'], el['bodovi']))

if __name__ == "__main__":
    main()