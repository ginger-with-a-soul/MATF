#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/
SEPARATOR = "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="

s1 = "the quick brown fox"
s2 = "jumped over the lazy dog"

# Stringove mozemo konkatenirati
haystack = s1 + " " + s2

# -------------------------------------------------------------------------------
# Trazenje podstringa (igla u plastu sena)
# -------------------------------------------------------------------------------
needle = "lazy"
i = haystack.find(needle)
print("haystack = \"%s\" needle = \"%s\"" % (haystack, needle))
print("indeks reci %s je %d" % (needle, i))

# -------------------------------------------------------------------------------
# Umetanje separatora u listu reci
# -------------------------------------------------------------------------------
reci = ["c++", "java", "python", "c", "c#", "haskell", "omgrofl", "go"]
csv = str.join(",", reci)   # vrlo zgodan metod u praksi
# ili (nad stringoom "," pozivamo metod join)
# csv = ",".join(reci)
# ili
print(csv)

# -------------------------------------------------------------------------------
# Tip i velicina karaktera
# -------------------------------------------------------------------------------
# Postoje metodi nad stringom koje mozemo koristiti da saznamo da li
# string sadrzi broj, malo slovo i slicno.
# isalnum, isalpha, isdigit, isidentifier, islower, isnumeric, isprintable, isspace...
# Menjanje malih u velika slova i obrnuto.
csv = csv.swapcase()
print("csv.swapcase(): %s" % csv)

# Leksikografsko sortiranje stringa
# t = sorted(s) vraca listu karaktera koji su sortirani leksikografski.
# "".join(t) spaja listu elemenata po praznom stringu, odnsono od liste karaktera
# pravi string (cesto se koristi u python-u)
print("Sortirano [%s]" % "".join(sorted(haystack)))

# -------------------------------------------------------------------------------
# Indeksiranje
# -------------------------------------------------------------------------------
# Slicno kao za nizove, stringove mozemo indeksirati koristeci operator [a:b]
print(SEPARATOR)
s = "abcdefghijkl"
print("s = \"%s\"" % s)
print("len(s) = %d" % len(s))
print("s[0:3] = \"%s\"" % s[0:3])       # od pocetka pa do 3 (bez 3)
print("s[8:] = \"%s\"" % s[8:])         # od indeksa 8 pa do kraja
print("s[8:9] = \"%s\"" % s[8:9])       # od indeksa 8 do 9 (bez 9)
# indeks -1 oznacava poslednji indeks u nizu, -2 pretposlednji itd.
# ako je n broj elemenata niza, -1 = n-1, -2 = n-2, -3 = n-3 ...
print("s[-3:-1] = \"%s\"" % s[-3:-1])
