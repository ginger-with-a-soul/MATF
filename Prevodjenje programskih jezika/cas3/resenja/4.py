#!/usr/bin/python3

import sys

# kreiramo skup na osnovu nekog strings
s = set("abrakadabra");
print (s)
# kreiramo neku listu
b = ['abrakadbra', 'primer', 'primer'];

# pravimo skup od string b
# BITNO: skup je skup u matematickom smislu, dakle nema ponavljanja elemenata
# svaka klasa ekvivalencije ima samo jednog predstavnika
print (set(b))

# provera da li se slovo f nalazi u skupu s
if 'f' not in s:
	# ubacujemo element u skup
	s.add('f')
	print ("slovo je izbaceno")
else:
	# ako se element nalazi u skupu izbacujemo ga
	s.remove('f')
	print ("slovo f je ubaceno")

# pravimo skup na osnovu nekog drugog stringa
c = set("primer1234")

# stampamo skupove
print (s)
print (c)

# presek dva skupa
print (s&c)
print (s.intersection(c))

# unija dva skupa
print (s|c)
print (s.union(c))

# razlika dva skupa
print (s-c)
print (s.difference(c))

# simetricna razlika dva skupa
print (s^c)
print (s.symmetric_difference(c))




