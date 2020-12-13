#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/

t = [7, 2, 1, 56, -3, 10, 14]

# Obrcemo listu (zovemo metod koji obrce elemente)
print("Obrnuta lista:")
t.reverse()
print(t)

# Sortiramo niz
print("Sortirana lista:")
t.sort()
print(t)

# Spajamo liste
y = [100, 200]
t.extend(y)
print("Spojena lista:")
print(t)

# Dodajmo elemente na pocetak i kraj liste.
t.append(1000)
t.insert(0, -1000)
print("Liste posle ubacivanjana pocetak i kraj")
print(t)

# remove(x) - uklanja prvi element iz liste koji je jednak x
t.remove(1)
print("Posle uklanjanja 1")
print(t)

# pop([i]) - poziv bez argumenata skida sa kraja i vraca element,
# ukoliko se prosledi i, onda skida element sa pozicije i koji vraca.
kraj_liste = t.pop()
sredina_liste = t.pop(len(t)//2)
print("kraj_liste = %d sredina_liste = %d" % (kraj_liste, sredina_liste))
print(t)

t.insert(3, 10)
t.extend([10, 10, 10])
print("Broj pojavljivanja broja 3: %d" % t.count(10))
