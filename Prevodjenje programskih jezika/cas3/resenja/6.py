#!/usr/bin/python3

import sys

# Recnik je struktura podataka koja dozvoljava mapiranje oblika kljuc:vrednost
# i kljuc i vrednost mogu da budu bilo koja struktura podataka

# Recnik se definise izmedju viticastih zagrada. Elementi recnika se razdvajaju zarezima
# Svaki element recnika je oblika kljuc:vrednost
lokal = {'Pera':123,'Zika':239,'Mika':187}

# stampamo recnik
print (lokal)

# BITNO: recnik je struktura koja nema uredjenje, tj. ne zna se koji je element prvi. a koji poslednji
# metod keys() vraca listu kljuceva u recniku
# metod values() vraca listu vrednosti u recniku
# liste koje se dobijaju pomocu metoda keys() i values() su 1-1, tj. kljucu na i-tom mestu u listi kljuceva
# odgovara vrednost na i-tom mestu u listi vrednosti
print (lokal.keys()) 	# lista kljuceva
print (lokal.values())	# lista vrednosti

print (sorted(lokal.keys())) # stampamo sortiranu listu kljuceva

# BITNO:
# pristup elementima recnika je moguc pomocu kljuca
# lokal['Pera']
# uz jedno vazno ogranicenje. Ako se element 'Pera' ne nalazi u recniku a mi pokusamo da koristimo
# tu vrednost, program automatski puca
#
# Pristup vrednostima u recniku uz pomoc kljuca se koristi samo onda kada ste sigurni da taj kljuc postoji
# u recniku
#
# U suprotnom se koristi metod get() koji vraca vrednost pridruzenu kljucu ili None ako se element ne nalazi u recniku
print (lokal.get('Laza'))

# proveravamo koliko elemenata ima u recniku
if (len(lokal) < 3):
	# stampamo recnik ako ima manje od 3 elementa
	print (lokal)
elif 'Laza' not in lokal.keys(): # proveramo da li se kljuc Laza nalazi u recniku
	# ako se ne nalazi, ubacujemo ga.
	lokal['Laza'] = 500;	
	# BITNO:
	# ako kljuc Laza postoji u recniku, ovakva naredba ce promeniti vrednost koja mu je pridruzena
	# ako kljuc Laza ne potoji u recniku, bice dodat u recnik i bice mu pridruzena vrednost 500
else:
	# ako je kljuc LAza u recniku, prikazujemo vrednost koja mu je pridruzena
	print (lokal['Laza'])
	
print (lokal)

# BITNO:
# metod zip kreira novu listu ntorki na osnovu argumenta
#
# U ovom slucaju kreirace se lista parova pri cemu je prva koordinata svakog para kljuc a druga
# koordinata je vrednost
print (zip(lokal.keys(), lokal.values()))

print (('Pera', 123) in zip(lokal.keys(), lokal.values()))	# ispitujemo da li se Pera sa lokalom 123 nalazi u listi parova
print (('Laza', 140) in zip(lokal.keys(), lokal.values()))  # ispitujemo da li se Laza sa lokalom 140 nalazi u listi parova

print (('Pera', 123) in lokal.iteritems()) # ispitujemo da li se Pera sa lokalom 123  nalazi u listi parova tako sto prvo kreiramo iterator nad listom

# stampamo recnik tako sto iteriramo kroz listu kljuceva i redom
# citamo vrednosti koju su pridruzene kljucevima iz liste
for k in lokal.keys():
	print (k, lokal[k])

print "\n"

# drugi nacin da odstampamo recnik je pomocu metoda items()
# koji vraca listu uredjenih parova oblika (kljuc, vrednost)
# iteriranjem kroz listu, odstampacemo recnik
for k,v in lokal.items():
	print (k,v)

# lamda izrazi. Funkcionalni stil progrmairanja, samo ilustracija
d = dict([(x, x**2) for x in range(1, 11)]);
print (d)

# BITNO:
# stringovi u pajtonu su imutabilni, tj. ne mogu se menjati
# ako hocemo da zamenimo svaku pojavu slova a sa slovom e
# potrebno je da napravimo novi string
a = "abrakadabra"
b = ""

# iteriramo slovo po slovo kroz string a i kreiramo novi string b
for c in a:
	# i ako se radi o slovu a
	if c == 'a':
		# u string b upisujemo slovo e
		b = b + 'e'
	else:
		# inace upisujemo polazno slovo
		b += c

# stampamo rezultat
print (a)
print (b)

# stampamo sve kvadrate neparnih brojeva u intervalu [1,10]
for i in range(1, 11, 2):
	print (i**2)
	

# iteriramo kroz listu i stampamo elemente nadovezane same na sebe 2 puta
l = ['ovo', 'je', 'neka', 'lista']
for i in l:
	print (i*2)
	
# BITNO:
# nikada ne smemo istovremeno da iteriramo kroz listu i da joj dodajemo/izbacujemo elemente
# Ako to zelimo treba da iteriramo kroz kopiju liste (l[:]) i da dodajemo elemente u originalnu listu
for i in l[:]:
	l.insert(0,i)
	
print (l)
	

