#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/

# Sa standardnog unosa unosimo n i ispisujemo sve parne brojeve
# od 0 do n.

# input(msg) na standardni izlaz ispisuje poruke i ceka unos
# korisnika.
# Unos korisnika se vraca kao string iz funkcije.
# Posto zelimo da unesemo broj, string prosledjujemo funkciji int(...)
# koja nam vraca broj.
n = int(input("Unesite broj: "))

# Celi brojevi iz intervala [1, n]
print("Parni brojevi:")
for i in range(1, n+1):
    if i % 2 == 0:
        print(i)

# PAZNJA:
# Operator / vrsi realno deljenje. Za celobrojno deljenje
# koristimo operator //.
# Slicno umesto /= koristimo //=.
print("Cifre broja:")
while n != 0:
    cifra = n % 10
    n //= 10
    print(cifra)
