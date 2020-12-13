#!/usr/bin/python3

# prva linija fajla je uvek putanja do interpretera

# ukljucivanje potrebnih modula
import re
import sys

# flagovi koji definisu korisnikov izbor
autor = False
godina = False
izdavac = False
cena = False

# na pocetku ne znamo da li je korisnik uneo naslov
naslov = None

# provera broja argumenata
if len(sys.argv) < 2:
	sys.exit('Neispravan poziv')

# parsiramo argumente komandne linije, pri cemu preskacemo
# sam poziv programa
for a in sys.argv[1:]:
	# u slucaju da je u pitanju opcija
	if a[0] == '-':
		if a[1] == 'a':
			autor =True
		elif a[1] == 'c':
			cena = True
		elif a[1] == 'i':
			izdavac =True
		elif a[1] == 'g':
			godina = True
		else:
			exit('Nepodrzana opcija')
	# u slucaju da nije opcija, radi se o naslovu
	else:
		naslov = a

# ako nismo naleteli na naslov, prekidamo izvrsavanje
if naslov is None:
	sys.exit('Jedan od argumenata mora biti naslov knjige')

# opet je ocigledno da se nas sablon nalazi u vise redova,
# pa ucitavamo ceo fajl
try:
	with open("knjige.xml","r") as f:
		datoteka = f.read()
except IOError:
	sys.exit('Neuspelo otvaranje datoteke knjige.xml')


# iz primera je ocigledno da redosled tagova moze da se menja
# i jedno moguce resenje takvog problema je upotreba preduvida
#
# Zbog nacina na koji preduvidi rade (binarno, tj. ima nema, neucestvovanja u samom
# poklapanju i vracanju na pocetni offset nakon evaluacije izraza), oni omogucavaju da
# prepoznamo sablone koji mogu da imaju permutovani sadrzaj.
#
# Takav pristup je u ovom resenju.
#
# BITNO: 
# preduvidi ne ucestvuju u samom poklapanju vec samo vrse proveru da li nesto
# postoji ili ne. Zbog takvog ponasanja, mi rucno moramo da poklopimo ono sto su
# preduvidi prepoznali i upravo to radi deo .*? u 73 liniji koda
# Kada bismo to zaboravili, ne bismo mogli da poklopimo nijednu knjigu
#
# BITNO2:
# iako preduvidi ne vrse poklapanje, sva imenovana grupisanja mozemo da koristimo kasnije
# bez ikakvih problema
ri = re.compile(r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[0-9]+)"\s*>\s*'
	+r"(?=.*?<naslov>\s*(?P<naslov>.*?)\s*</naslov>)"
	+r"(?=.*?<autor>\s*(?P<autor>[A-Z][a-z]+(?:\s+[A-Z][a-z]+)+)\s*</autor>)"
	+r'(?=.*?<cena\s+valuta\s*=\s*"(?P<valuta>rsd|eur)">\s*(?P<cena>[1-9][0-9]*)\s*</cena>)'
	+r"(?=.*?<izdavac>\s*(?P<izd>.*?)\s*</izdavac>)"
	+r"(?=.*?<godina_izdanja>\s*(?P<godina>[0-9]+)\s*</godina_izdanja>)"
	+r".*?</knjiga>", re.S)	
# Drugi nacin kako ovo moze da se resi je da imate 6 regulatnih izraza kojima cete da
# prepoznajete razlicite delove samog sablona, tj. knjige
# 1 regex za izdvajanje knjiga.
# 	I kada izdvojite knjigu, jos 5 regex-a za prepoznavanje svakog atributa koji je pridruzen
#	knjizi
#
# Ovaj pristup je mozda ocigledniji, ali mnogo tezi za pravilno izvodjenje, jer zahteva
# mnogo ozbiljniju proveru gresaka
#
# Pokusajte da uradite ovo za domaci i videcete koliko je teze.

# BITNO3:
# kada radite zadatke, najvaznije je da pravilno izaberete kolekciju kojom cete da 
# organizujete podatke u svom programu. Pogresan izbor kolekcije moze eksponencijalno da
# oteza sam zadatak.
#
# Ovde je ocigledno da je svaka knjiga opisana svojim rednim brojem kojem su pridruzene 
# neke informacije. Mapiranja ovog tipa, treba da vas asociraju na recnik, i to cemo da 
# koristimo u ovom resenju
# Kljuc ce biti redni broj, a vrednost ce biti lista informacija
biblioteka = {}
# Svaki unos u recniku je sledeceg oblika
# redni_broj -> naslov, autor, godina, izdavac, cena, valuta

# iteriramo kroz sva uspesna poklapanja
for m in ri.finditer(datoteka):
	# i ubacujemo ih u recnik u ranije pomenutom formatu
	biblioteka[m.group('rbr')] = [m.group('naslov'), m.group('autor'),m.group('godina'),m.group('izd'),m.group('cena'),m.group('valuta')]
	#print biblioteka[m.group('rbr')]

# da se uverimo da smo lepo pokupili podatke
# for (k,v) in biblioteka.items():
#	print(k,v)

# pretrazujemo recnik po naslovu
vrednosti = None;
for k,v in biblioteka.iteritems():
	if v[0] == naslov:
		vrednosti = v[1:]
		break

# ako nismo nasli knjigu sa zadatim naslovom, prekidamo program
if vrednosti is None:
	sys.exit('Nepostoji knjiga sa naslovom "%s"' %naslov)

# stampamo sve ono sto zeli korisnik
if autor :
	print (vrednosti[0])
if godina:
	print (vrednosti[1])
if izdavac:
	print (vrednosti[2])
if cena:
	print (vrednosti[3], vrednosti[4])

# ako nema opcije, stampamo sve
if (autor or godina or cena or izdavac) == False:
	for v in vrednosti:
		print (v) 