#!/usr/bin/python3

import sys

# BITNO:
# sys.argv je lista argumenata komandne linije
# argumenti komandne linije se ponasaju identicno kao u C-u
# inbdeksiranje krece od 0 i 0 argument je uvek sam poziv programa
#
# argumentima komandne linije se pristupa iskljucivo sa sys.argv
# ako se izostavi sys to je onda samo lokalna promenljiva sa imenom argv,
# a ne lista argumenata komandne linije
if len(sys.argv) < 2:
	sys.exit("Nedovoljan broj args")

# prikazujemo sve argumente
for arg in sys.argv:
	print (arg)
	
# stampamo argumente komandne linije kao listu
print (sys.argv)

try:
	# otvaramo fajl u modu za citanje
	f = open(sys.argv[1], "r")
except IOError:
	# obrada gresaka je obavezna, i ovde se radi hvatanjem izuzetaka
	sys.exit("fajl ne postoji")
	
# stampamo fajl liniju po liniju
for l in f:
	print (l)

# alternativno
#for l in f.readlines():
#	print (l)

# na kraju obavezno zatvaramo fajl
f.close()


