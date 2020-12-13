#!/usr/bin/python3

import sys

broj_nula = 0

while True:
	try:
		c = input('Unesite 0 ili 1: ')
		if (c != '0' and c !='1' ):
			raise ValueError('Nije uneta ni 0 ni 1')
	except EOFError:
		break
	except ValueError as e:
		print (e)
		sys.exit()
		
	if c== '0':
		broj_nula += 1
		
if(broj_nula % 2 == 0):
	print (Unet je paran broj 0")
else:
	print ("Na uzlazu imamo neparan broj nula")

