#!/usr/bin/python3

import sys

pitanja = ['ime', 'prezime', 'mesto']
odgovori = ['pera','peric','matf']

for a,b in zip(pitanja, odgovori):
	print("Tvoje {0}: Moje {0} je {1:10}".format(a,b))
	
for a,b in zip(pitanja, odgovori):
	print("Tvoje %s: Moje %s je %10s"%(a,a,b))
	

for a,b in zip(pitanja, odgovori):
	print("Tvoje %(pitanje)s: Moje %(pitanje)s je %(odgovor)s"%{"pitanje":a, "odgovor":b})
	
