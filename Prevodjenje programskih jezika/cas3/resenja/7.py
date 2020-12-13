#!/usr/bin/python3

import sys

# liste koje cemo da zipujemo
pitanja = ['ime', 'prezime', 'mesto']
odgovori = ['Pera', 'Peric', 'Beograd']

# formatiranje izlaza
for a,b in zip(pitanja, odgovori):
	print ("Tvoje {0}: Moje {0} je {1:10}".format(a, b))

print "\n"
for a,b in zip(pitanja, odgovori):
	print ("Tvoje %s: Moje %s je %10s"%(a, a, b))
	
for a,b in zip(pitanja, odgovori):
	print ("Tvoje %(pit)s: Moje %(pit)s je %(odg)10s"%{"pit":a, "odg":b})
