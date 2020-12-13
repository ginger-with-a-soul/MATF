#!/usr/bin/python3

import sys
import re

# proveravamo broj argumenata komandne linije
if len(sys.argv) < 2:
	sys.exit("./10.py filePath")

# proveramo da li prosledjeni string ima ekstenziju .txt
# pri cemo smo ukljucili ignore case mod prilikom poklapanja
# tako sto smo naveli re.I kao opciju prilikom pretrage
if re.match(r'.+\.txt', sys.argv[1], re.I) is None:
	exit("Fajl mora da bude .txt")
	
# za slozenija ili visetruka poredjenja, u programima treba da koristimo
# kompajlirane regularne izraze
ri = re.compile(r'(?i)(\b[A-Za-z]+\b)\s+\1')

# ucitavamo sadrzaj fajla
# Deo pod komentarom je siican using konceptu iz C#, i ovde cemo ga koristiti da bismo
# ucitali ceo fajl i tumacili ga kao jednu jedinu liniju
try:
	#with open(sys.argv[1], "r") as  f:
	f = open(sys.argv[1], "r")
	#	datoteka = f.read()
except IOError:
	sys.exit("fajl ne postoji")

# u svakoj liniji fajla
for linija in f:
	# pronalazimo prvo poklapanje.
	# BITNO:
	# search metod trazi samo prvo poklapanje u liniji i tu staje.
	# slicno kao sed alat u podrazumevanom modu
	match = ri.search(linija)
	# ako je poklapanje uspelo
	if match is not None:
		# stampamo poklapanja
		# m.group() izdvaja kompletno poklapanje
		# m.group(i) izdvaja samo zagradu pod rednim brojem i u okciru regularnog izraza (tj. bekreferencu, \i za i > 1)
		#			 u slucaju da je i == 0, poziv je ekvivalentan sa m.group()
		# m.groups() izdvaja sve grupe koje postoje u izvrsenom poklapanju
		print ("Poklapanje: %s\t groups: %s"%(match.group(), match.groups()))
		# ri.sub(...), metod menja poklopljeni deo sa recima "bilo sta" u stringu linija
		print ("Linija bez ponavljanja: " + ri.sub('bilo sta', linija))

#print datoteka


# drugi nacin izdvajanja poklapanja je pomocu findited() metoda koji omogucavaj lako i brzo obradjivanje poklapanja
#for m in re.finditer(r'\b(\w+)\b\s+\1', datoteka, re.I):
#	print m.group()

# obavezno zatvaramo fajl ako ga nismo otvarali sa with....
f.close()
