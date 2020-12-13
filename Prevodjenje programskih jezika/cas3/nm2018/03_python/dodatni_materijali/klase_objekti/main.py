#! /usr/bin/env python
# -*- coding: utf-8 -*-

# Koristimo kada nam je potrebna konkretna klasa iz datoteke.
# "iz datoteke tacka.py ucitaj klasu Tacka"
from tacka import Tacka

# Mozemo ucitati celu datoteku (modul), no onda smo duzni
# da elementima modula pristupamo kroz njegovo ime.
# To znaci da ne postoji klasa Tacka vec tacka.Tacka
# import tacka

import random

t = Tacka(2, 3)
print(t)

# Generisemo 10 nasumicnih tacka.
n = 10
ts = []
for i in range(10): ts.append(Tacka(random.uniform(0, 40), random.uniform(0, 40)))

# Sortiramo tacke
print(ts)
# ts = sorted(ts)
# print(list(map(str, ts)))

t1 = Tacka(10, 10)
t2 = Tacka(20, 20)

# + poziva t1.__add__(t2) sto daje objekat klase 'Tacka', potom python
# poziva metod .__str__() i ispisuje dobijeni string.
print(t1 + t2)

print("Ukupno napravljeno tacaka: %d" % Tacka.broj_tacaka)
