#!/usr/bin/python3

import sys
import re	# kada god hocemo da koristimo regularne izraze moramo da importujemo re modul

# proveravamo broj argumenata komandne linije
if len(sys.argv) < 2:
	sys.exit("Nedovoljan broj argumenata")
	
# re.match metod sluzi za proveru da li se prosledjeni string poklapa sa zadatim 
# regularnim izrazom
# BITNO:
# match uvek radi poklapanje od pocetka stringa. match metod ne treba da se koristi
# ako vam treba poklapanje na proizvoljnom polazaju u stringu
# BITNO2:
# regulatne izraze uvek zadajte kao sirove stringove, tj. ispred stringa stavite slovo r
# na taj nacin ne morate da brinete o specijalnim karakterima

# pomocu re.match metoda proveramo da li je ekstenzija prosledjenog argumenta .txt
uparivac = re.match(r'.+\.txt', sys.argv[1], re.I);

# ako poklapanje uspe, match metod vraca bas poklopljeni deo stringa, u suprotnom vraca None

# proverom povratne vrednosti, odlucujemo sta prikazujemo korisniku
if uparivac is None:
	print ("Fajl mora da bude .txt")
else :
	print ("argument je ispravan")
