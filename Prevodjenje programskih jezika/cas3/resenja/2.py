#!/usr/bin/python3

# stringovi u pajtonu
import sys


s = "Hello world\n"
print (s)

# BITNO:
# stringovi u pajtonu su imutabilni, tj. ne mozete da ih menjate
# ako treba da menjate string, potrebno je da napravite novi sa izmenjenim
# sadrzajem

# sa tim u vezi, ovakva naredba prijavljuje sintaksnu gresku
# s[2] = 'Z'

print (s + s)	# nadovezivanje stringova
print (s*3)		# nadovezivanje stringa s 3 puta

# "sirovi" string, tj. string se stampa doslovno, bez tumacenja specijalnih karaktera
print (r'Ovo\tje\ndoslovni\ttekst\n')

# string koji se prostrire na vise redova i stampa se u navedenom obliku
print ("""dsjhjfksdhf
dsflkjsdhfkjdh
dsflkjsdhkjfldhs
dsfjlksdfk""")

# Pored indeksiranje stringova na nacin na koji C to radi, Python podrzava
# i indeksiranje unazad.
#
#   H   e   l  l  o     w  o  r  l  d \n
#   0   1   2  3  4  5  6  7  8  9 10 11
# -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1

# Indeksni pristup
print (s[2])   		# drugo slovo
print (s[-5])		# peto slovo otpozadi
print (s[2:7])		# podstring od drugog do sestog slova
					# BITNO:
					# indeksiranje u opstem obliku s[>=, <]
					# prvi broj se uvek ukljucuje, dok se drugi broj nikad 
					# ne ukljucuje u podstring

print (s[2:])		# izostavljanje drugo argumenta znaci "do kraja". Od drugog slova do kraja
print (s[:7])		# izostavljanje prvog argumenta znaci "od pocetka"
print (s[-5:-1])	# moguce je negativno indeksiranje

# funkcija len() vraca duzinu, tj. broj elemenata kolekcije
print s[-10:len(s)-1]

