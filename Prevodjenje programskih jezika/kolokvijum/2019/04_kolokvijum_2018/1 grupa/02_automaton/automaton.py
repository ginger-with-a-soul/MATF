#! /usr/bin/env python
# -*- coding: utf-8 -*-
import sys


def main():
    user_input = ""

    print('Unesite cifru po cifru.\nDozvoljene cifru su 0 i 1.\nUlaz prekidate signalom EOF (Ctrl+D).')

    stanje = 1
    zavrsna = [4, 5]
    prelaz = {
        (1, 0): 2,
        (1, 1): 3,
        (2, 0): 5,
        (2, 1): 3,
        (3, 0): 2,
        (3, 1): 4,
        (4, 0): 2,
        (4, 1): 4,
        (5, 0): 5,
        (5, 1): 3,
    }

    while True:
        try:
            c = input()
            user_input += c
            c = int(c)
            if c != 0 and c !=1:
                raise ValueError('Nije uneta ni 0 ni 1')
        except EOFError:
            break
        except ValueError as e:
            print(e)
            sys.exit()

        stanje = prelaz[(stanje, c)]
        print("Trenutno stanje: {}".format(stanje))


    print("Korisnicki unos: ", user_input)
    if stanje in zavrsna:
        print("Ulaz je u odgovarajucem obliku.")
    else:
        print("Greska u ulazu.")


if __name__ == "__main__":
    main()
