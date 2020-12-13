#! /usr/bin/env python

import sys

def main():

    zavrsno_stanje = "P"
    pocetno_stanje = "P"

    user_input = ""

    prelaz = {
        ('P', '0') : 'N',
        ('P', '1') : 'P',
        ('N', '0') : 'P',
        ('N', '1') : 'N',
    }
    
    while True:
        try:
            c = str(input())
            user_input += c
            if c != '1' and c != '0':
                raise ValueError('Nije uneta ni 0 ni 1')
        except EOFError:
            break
        except ValueError as e:
            print(e)
            sys.exit()



        pocetno_stanje = prelaz[(pocetno_stanje, c)]

    print(user_input)
    if pocetno_stanje == zavrsno_stanje:
        print("Paran broj 0")
    else:
        print("Neparan broj 0")

if __name__ == "__main__":
    main()