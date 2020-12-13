#!/usr/bin/python3

import sys

# ucitavamo nesto sa standardnog ulaza
# i to eksplicitno kastujemo u int
x = int(input("Unesite broj"))

print (x/2) # kolicnik 
print (x%2)	# ostatak

# BITNO:
# blokovi u pajtonu pocinju sa :
# Sve sto je uveceno je deo bloka, prvi put kada se "razbije" uvlacenje
# prekida se blok

# proveravamo da li je broj veci od 1000
if (x > 1000):
	print ("Broj je veci od hiljadu")
else:
	# ako nije, pitamo se da li je broj paran ili ne
	if (x % 2 == 1):
		print ("Broj je neparan")
	else:
		print ("Broj je paran")
	# stampa se svakako jer je deo prvog else bloka
	print ("Broj je manji od hiljadu")

print ("Ovo se stampa u svakom slucaju")


	

