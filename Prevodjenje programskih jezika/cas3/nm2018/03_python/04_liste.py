#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/

# Pravimo listu podataka
lista = [1, 2, 3, 4, 5, 6, 7, 8, 9]

print("Duzine liste %d" % len(lista))

print("Elementi prve liste:")
# Za svaki element x u listi
for x in lista:
    print(x)


# U liste mozemo stavljati razlicite tipove.
print("Elementi druge liste:")
lista = ["Zdravo", "studenti", 10, 20, [1, 2, 3]]
for x in lista:
    print(x)

i = 4
# Posto nismo sigurni sta je tip unutar liste, mozemo koristiti
# format %s koji poziva funkciju str() nad promenljivom pre nego sto je ispise.
# U nasem slucaju pozivali bi se str(10), str(20), str([1,2 , 3])...
print("lista[%d] = %s" % (i, lista[i]))
