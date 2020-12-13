#!/usr/bin/python3

# prva linija fajla je uvek putanja do interpretera

# ukljucivanje potrebnih modula
import re
import sys

# provera ulaznih argumenata
if len(sys.argv)!=2:
	sys.exit('Program se poziva sa: python '+sys.argv[0] + "datoteka")

# ako je u zadatku eksplicitno navedena ekstenzija ulaznog fajla, neophodno
# je proveriti da li je fajl bas te ekstenzije
#
# u regularnom izrazu koji opisuje fajl sa zadatom ekstenzijom, kapica (sidro) na pocetku
# je opciono zbog samog nacina kako radi re.match()
if re.match(r"^[\w_-]+\.stn$",sys.argv[1]) is None:  
	sys.exit('Prosledjena datoteka mora biti ekstenzije .stn!')

# ucitavanje fajla. iz primera se vidi da ono sto treba da prepoznamo
# moze da se nalazi u vise redova, pa je ocigledno da moramo da ucitamo ceo
# fajl u program
try:
	with open(sys.argv[1],"r") as f:
		fajl = f.read()
except IOError:
	sys.exit('Neuspelo otvaranje i citanje datoteke ' +sys.argv[1] )
	
	
# regularni izraz koji opisuje sablon koji trazimo. 
# Kada kreirate regularni izraz koji opisuje sablon, prvo pazljivo
# proanalizirajte sta je to sto treba da poklopite i sta sa tim poklapanjem 
# treba da uradite. Tek onda pravite izraz.
#
# U ovom slucaju, prvo treba da uocimo da je ono sto pretrazujemo uokvireno
# viticastim zagradama, pa ce ivice izraza biti
# {}
# zatim treba da uocimo koji su delovi izraza koji su konstanti. To su ,.NE+ i :, 
# koji su praceni nekim drugim karakterima. To sta se oko njih nalazi nama sluzi da
# napravimo xml tagove, pa treba da ih grupisemo radi kasnije lakse zamene
# 
# {(neki tekst),.NE+(tag):brojslovo}
#
# Sada ostaje samo da opisemo nedostajuce delove regularnog izraza
#
# neki tekst ocigledno moze da bude bilo sta, dakle .*
# ali sa ovim treba da budemo oprezni, jer je zvezda pohlepna pa ce jesti karaktere
# sve do poslednje }
# Da se to ne bi desilo treba da joj iskljucimo pohlepnost sa ?
# neki tekst -> (.*?)
#
# Tag je neka kombinacija malih slova -> ([a-z]+)
# broj -> [0-9]
# slovo -> [a-z]
#
# i sve ovo kada sklopimo u celinu dobijamo regularni izraz koji opisuje nas sablon
#
# {(.*?),\.NE\+([a-z]+):[0-9][a-z]}
uzorak=re.compile(r'{(.*?),\.NE\+([a-z]+):[0-9][a-z]}',re.S)

# sada ostaje da svako prepoznavanje sablona zamenimo ispravnim xml tagom
#
# Ovde je osetljivo mesto, jer ovo treba da izvedete sto je lakse i elegantnije moguce.
# C pristup u kome korak po korak menjate svaku prepoznavanje je izuzetno tezak, jer sve 
# vreme treba da vodite racuna o file offsetu i ovo je nesto sto nije u duhu python
# progrmairanja.
# Treba vam zamena svakog prepoznavanja u fajlu ->  treba vam sub metod koji bas to.
#
# Kada imate kompajliran regularni izraz, bez problema mozete da koriste bek reference koje 
# ste u njemu definisali. 
# BITNO: sub metod ne radi u mestu, vec kreira novi string
zamena = uzorak.sub(r"<\2>\1</\2>", fajl)

# upisujemo rezultate u fajl
try:
	with open(sys.argv[1][:-3]+"xml","w") as fxml:
		# BITNO: f.write ne dodaje nove redove kao sto to radi print, 
		# vec direktno zapisuje bajtove
		fxml.write("<xml>\n")
		fxml.write(zamena)
		fxml.write("\n</xml>")
		# alternativno:
		# fxml.write("<xml>\n" + zamena + "\n</xml>\n")
		
except IOError:
	sys.exit('Neuspelo otvaranje i citanje datoteke jat.xml')
	
