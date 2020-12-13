#! /usr/bin/env python

import sys
import re

def f1(data, reg):

    lista = []

    for x in reg.finditer(data):
        n = float(x.group('golovi')) / float(x.group('utakmice'))
        lista.append({
            'ime' : x.group('ime'), 
            'koeficijent' : n
        })

    def komparator(el):
        return el['koeficijent']

    lista.sort(key=komparator, reverse=True)

    for el in lista:
        print(el['ime'] + " " + "{:.2f}".format(el['koeficijent']))
        

def f2(data, reg, klub):


    for x in reg.finditer(data):
        s = str(x.group('klubovi'))
        prvi_datum = int(x.group('datum1'))
        if klub in s:
            if x.group('datum2') == None:
                godina = 2018
            else:
                godina = int(x.group('datum2'))
            razlika = godina - prvi_datum
            print(x.group('ime') + " %i %i" % (prvi_datum, razlika))    


def main():

    num = len(sys.argv)
    if num < 3:
        sys.exit("Bad arg count")

    input_path = sys.argv[1]
    
    if not input_path.endswith(".csv"):
        sys.exit("Bad input file name")
    
    try:
        with open(input_path, "r") as f:
            data = f.read()
    except IOError as e:
        sys.exit(e.message)

    
    reg = re.compile(r"(?P<ime>[A-Z][a-z]*\s?([A-Z]?[a-z]*)?\s?([A-Z][a-z]*)?\s?),\s*(?P<drzava>[A-Z][a-z]*),\s*(?P<golovi>[1-9][0-9]*),\s*(?P<utakmice>[1-9][0-9]*),\s*(?P<datum1>[0-9]{4})-(?P<datum2>[0-9]{4})?,\s*(?P<klubovi>([A-Z][a-z0-9, ]*)+)")

    klub = ' '.join(sys.argv[3:])

    if sys.argv[2] == "-g":
        f1(data, reg)
    elif sys.argv[2] == "-t":
        f2(data, reg, klub)
    else:
        sys.exit("Bad option arg")

if __name__ == "__main__":
    main()