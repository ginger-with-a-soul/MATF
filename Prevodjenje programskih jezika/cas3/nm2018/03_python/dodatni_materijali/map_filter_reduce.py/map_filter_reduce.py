#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/

# Lambde (anonimne funkcije) omogucavaju vrlo ekspresivan kod
# koji cesto moze biti vrlo ekspresivan i lakse za razumevanje od standardnog.
import math

# -------------------------------------------------------------------------------
#  _ __ ___   __ _ _ __
# | '_ ` _ \ / _` | '_ \
# | | | | | | (_| | |_) |
# |_| |_| |_|\__,_| .__/
#                 |_|
# -------------------------------------------------------------------------------
def kvadriraj(x): return x*x
def korenuj(x): return math.sqrt(x)

# Prvih 10 brojeva
brojevi = list(range(1, 11))
print(brojevi)

# Kvadriramo sve brojeve
# tipican kod
# for x in brojevi:
    # x = x*x
# print(brojevi)
# koji jos i ne radi jer se dobijaju kopije brojeve iz liste.
# Drugi nacin:
# for i in range(len(brojevi))
    # brojevi[i] *= brojevi[i]

# Moze to lepse.
# Funkcija map(a, b), primenjuje funkciju 'a' nad svakim od elemenata od 'b'
# i vraca iterator kroz kolekciju koja se dobije nakon njene primene.
kvadrirani = map(kvadriraj, brojevi)
print("Kvadrati originalne liste %s" % list(kvadrirani))

korenovani = map(korenuj, brojevi)
print("Korenovana originalna lista %s" % list(korenovani))

# Sta ako nam funkcije u mapiranju zatreba samo na bas tom mestu i nigde
# drugde u kodu?
# Pravimo 'anonimnu' funkciju koju na licu mesta prosledjujemo funkciji 'map'.
kvadrirani = map(lambda x: x*x, brojevi)
print("Kvadrati originalne liste %s" % list(kvadrirani))

# -------------------------------------------------------------------------------
#   __ _ _ _
#  / _(_) | |_ ___ _ __
# | |_| | | __/ _ \ '__|
# |  _| | | ||  __/ |
# |_| |_|_|\__\___|_|
# -------------------------------------------------------------------------------
# Filter nam omogucava da iz kolekcije zadrzimo samo elemente
# koji zadovoljavaju predikat koji se prosledi.
def paran(x): return x % 2 == 0
def dvocifren(x): return x > 9 and x < 100

brojevi = list(range(1, 25))
print("Parni brojevi %s" % list(filter(paran, brojevi)))

# Koliko postoji brojeva deljivih sa 7 iz intervala [1, 10000] ?
res = len(list(filter(lambda x: x % 7 == 0, list(range(1, 10001)))))
print("Brojevi deljivi sa 7 iz intervala [1, 10000] = %d" % res)

# -------------------------------------------------------------------------------
#               _
#  _ __ ___  __| |_   _  ___ ___
# | '__/ _ \/ _` | | | |/ __/ _ \
# | | |  __/ (_| | |_| | (_|  __/
# |_|  \___|\__,_|\__,_|\___\___|
# -------------------------------------------------------------------------------
# Reduce omogucava da kolekciju redukujemo na jedan element
# koristeci funkciju. Tipican primer je sumiranje liste.

import functools
brojevi = list(range(1, 25))
zbir = functools.reduce(lambda x, y: x + y, brojevi)
print("zbir = %d" % zbir)

# Proizvod celih brojeva iz intervala [5, 10]
proizvod = functools.reduce(lambda x, y: x * y, range(5, 11))
print("Proizvod celih brojeva iz intervala [5, 10]: %d" % proizvod)
