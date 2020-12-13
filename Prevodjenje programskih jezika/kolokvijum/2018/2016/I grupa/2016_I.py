#! /usr/bin/env python

import sys
import re

def main():

    if len(sys.argv) != 2:
        sys.exit("Bad arg count")
    
    if not sys.argv[1].endswith(".csv"):
        sys.exit("Bad file ext")
    
    try:
        with open(sys.argv[1], "r") as f:
            data = f.read()
    except IOError as e:
        sys.exit(e.message)

    reg = re.compile(r"(?P<timestamp>[0-3][0-9]/[01][0-9]/[0-9]{4}\s[0-2][0-9]:[0-5][0-9]:[0-5][0-9]),(?P<ime>[A-Z][a-z]*)\s(?P<prezime>[A-Z][a-z]*),(?P<indeks>([1-9]|[1-9][0-9]|[1-3][0-9][0-9]|4[0-4][0-9]|450)/[0-9]{4}),(?P<grupa>[12]),(?P<razlog>.*)?")

    i = 0
    j = 0
    for x in reg.finditer(data):
        if x.group('grupa') == "1":
            ime = str(x.group('ime'))
            prezime = str(x.group('prezime'))
            indeks = str(x.group('indeks'))
            razlog = str(x.group('razlog'))
            grupa = str(x.group('grupa'))
            i += 1
            if not x.group('razlog') == None:
                print("%i %s %s %s %s %s"  % (i, indeks, ime, prezime, grupa, razlog))

    for x in reg.finditer(data):
        if x.group('grupa') == "1":
            i += 1
            if x.group('razlog') == None:
                print("%i " + x.group('indeks') + " " + x.group('ime') + " " + x.group('prezime') + " " + x.group('grupa') + "-" % (i))
    print(" ")
    for x in reg.finditer(data):
        if x.group('grupa') == "2":
            ime = str(x.group('ime'))
            prezime = str(x.group('prezime'))
            indeks = str(x.group('indeks'))
            razlog = str(x.group('razlog'))
            grupa = str(x.group('grupa'))
            j += 1
            if not x.group('razlog') == None:
                print("%i %s %s %s %s %s"  % (j, indeks, ime, prezime, grupa, razlog))

    for x in reg.finditer(data):
        if x.group('grupa') == "2":
            i += 1
            if x.group('razlog') == None:
                print("%i " + x.group('indeks') + " " + x.group('ime') + " " + x.group('prezime') + " " + x.group('grupa') + "-" % (j))



if __name__ == "__main__":
    main()