#!/usr/bin/python3

import sys

prelaz = {('AC','a'):'B', ('AC','b'):'AC',
			('B','a'):'B', ('B','b'):'D',
			('D','a'):'B', ('D','b'):'E',
			('E','a'):'B', ('E','b'):'AC'}


prelaz = {('P', '0'):'N', ('P', '1'):'P',
		 ('N', '0'):'P', ('N', '1') : 'N'}

stanje = 'AC'
zavrsno = 'E'

while True:
	try:
		c = input("Unesite nula ili jedan")
		if (c != 'a' and c != 'b'):
			raise ValueError("pogresna vrednost")
	except ValueError as e:
		print(e)
		sys.exit()
	except EOFError:
		break;
		
	if prelaz.get((stanje, c)) is not None:
		stanje = prelaz[(stanje, c)]
	else:
		sys.exit("Greska")
			
if stanje == zavrsno:
	print("Automat prihvate rec")
else:
	print("Automat ne prihvate rec") 
