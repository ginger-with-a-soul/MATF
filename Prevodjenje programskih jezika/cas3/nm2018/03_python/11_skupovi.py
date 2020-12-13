#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/

# Python poseduje tip 'set' koji je inspirisan skupovima u matematici.

# Prvi nacin da se inicijalizuje skup
s1 = set([1, 2, 3, 4, 5, 6])

# Drugi nacin da se inicijalizuje skup (napomena: {} pravi praznu MAPU ne SKUP)
s2 = {4, 5, 6, 7, 8, 9}

# Iteriranje
print("s1:")
for s in s1:
    print("* %d" % s)

print("s2: %s" % str(s2))

# Indeksiranje - ne mozemo indeksirati skup (izbacuje se greska)
# print("\ns1[0] = %d" % s1[0])

# Skupovne operacije
print("s1 ∪ s2 = %s" % str(s1.union(s2)))
print("s1 ∩ s2 = %s" % str(s1.intersection(s2)))
print("s1 / s2 = %s" % str(s1.difference(s2)))
print("s1 disjunktno s2 = %s" % str(s1.isdisjoint(s2)))

s11 = {2, 3}
if s11.issubset(s1):
    print("s11 = %s je podskup skupa s1 = %s" % (str(s11), str(s1)))

# Dodavanje
s1.add(7)
s1.add(8)
print("s1 nakon dodavanja: %s" % s1)

# Brisanje
s1.remove(8)
s1.discard(7)
# Razlika izmedju 'remove' i 'discard':
# https://stackoverflow.com/questions/44074695/what-is-difference-between-discard-and-remove-function-in-python-3-sets
print("s1 nakon brisanja: %s" % s1)
