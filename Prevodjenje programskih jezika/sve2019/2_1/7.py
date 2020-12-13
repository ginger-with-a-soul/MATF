#!/usr/bin/python3

import sys

pitanja = ["ime","prezime","mesto"]
odgovori = ["pera", "peric", "matf"]

for p,o in zip(pitanja,odgovori):
	print("Tvoje {0}: Moje {0} je {1}".format(p, o));
	
for p,o in zip(pitanja,odgovori):
	print("Tvoje %s: Moje %s je %10s"%(p,p,o))
	
for p,o in zip(pitanja,odgovori):
	print("Tvoje %(pitanje)s: Moje %(pitanje)s je %(odgovor)10s"%{"pitanje":p,"odgovor":o});
	

