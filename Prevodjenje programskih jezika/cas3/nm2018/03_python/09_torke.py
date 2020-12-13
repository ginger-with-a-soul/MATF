#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/
# -------------------------------------------------------------------------------
# N-torke su struktura podataka u Python-u koji navodimo
# izmedju obicnih zagrada i modeluju uredjene n-torke u matematici.
# Na engleskom se nazivaju 'tuple' odnosno 'tuples' (mnozina).
# -------------------------------------------------------------------------------

# ------------------------------------------------------------------------------- # Inicijalizacija torki # -------------------------------------------------------------------------------
# Inicijalizacija n-torki
# ------------------------------------------------------------------------------- # Inicijalizacija torki # -------------------------------------------------------------------------------
# Prazna N-torka n = 0
n_0 = ()
# n = 1
n_1 = (10,)         # , nam je potreban ako zelimo n-torku
# n = 2
n_2 = (10, 20)

# -------------------------------------------------------------------------------
# N-torke mozemo konkatenirati.
# Primetimo da se ne vrsi sabiranje po elementima, vec se pravi
# nova n-torka ciji ce elementi biti elementi torke p1 i p2.
# -------------------------------------------------------------------------------
# Pravimo nekoliko tacaka
p1 = (3, 5)
p2 = (1, 3)

p3 = p1 + p2
print(p3)

# -------------------------------------------------------------------------------
# Broj elemenata n-torke.
# -------------------------------------------------------------------------------
print("broje elemenata p3: %d" % len(p3))

# -------------------------------------------------------------------------------
# Indeksiranje
# -------------------------------------------------------------------------------
print("p3[0] = %d" % p3[0])

# -------------------------------------------------------------------------------
# Iteriranje
# -------------------------------------------------------------------------------
print("Iteriranje")
for element in p3:
    print(element)


# -------------------------------------------------------------------------------
# Nije dozvoljeno menjanje elemenata N-torke (kod pod komentarom dovodi do greske)
# -------------------------------------------------------------------------------
# p3[0] = 100

# -------------------------------------------------------------------------------
# N-torke omogucavaju da iz funkcije vratimo vise vrednosti, ali i da
# "raspakujemo" povratne vrednosti.
# -------------------------------------------------------------------------------
def increment(x, y):
    x += 1
    y += 1
    return (x, y)

# Konstruise torku i "razmotava" je u promenljive 'a' i 'b'.
(a, b) = increment(10, 100)
print(a)
print(b)

# -------------------------------------------------------------------------------
# N-torke podrzavaju "slicing", odnosno da uzmemo podskup susednih elemenata.
# -------------------------------------------------------------------------------
elements = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
sliced = elements[2:6]
# str(x) gde je x torka pretvara torku u ispis
print("elements[2:6] = %s" % str(sliced))

# Provera pripadnosti
if 4 in elements:
    print("4 pripada %s" % str(elements))
else:
    print("4 ne pripada %s" % str(elements))

# -------------------------------------------------------------------------------
# Repliciranje torki
# -------------------------------------------------------------------------------
# Primena operatora * nad n-torkom multiplicira n-torku.
elements = (1, 2) * 4
print("(1, 2) * 4 = %s" % str(elements))
