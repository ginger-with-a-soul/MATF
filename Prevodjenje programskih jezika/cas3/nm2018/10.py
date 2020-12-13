#! /usr/bin/env python

#napraviti mapu, iterirati po njoj, napraviti listu od k, v
def main():

    mapa = {
        "prvi": 1,
        "drugi": 2, 
        "treci": 3,
        "cetvrti": 4,
        "peti": 5
    }

    for (k, v) in mapa.items():
        print("\"%s\" : %s" % (str(k), str(v)))

    if "prvi" in mapa:
        print("Tu!")
    else:
        print("Nije tu!")

    kljucevi = list(mapa.keys())
    vrednosti = list(mapa.values())

if __name__ == "__main__":
    main()