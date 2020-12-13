#!/usr/bin/python3

import sys

stanje = 'P'
zavrsno ='P'

while True:
	try:
		c = input('Unesite 0 ili 1: ')
		if (c != '0' and c !='1' ):
			raise ValueError('Nije uneta ni 0 ni 1')
	except EOFError:
		break
	except ValueError as e:
		print(e)
		sys.exit()
 
	if c == '0':
		if stanje == 'P':
			stanje = 'N'
		else:	
			stanje = 'P'
	
if stanje == zavrsno :
	print ('Rec ima paran broj nula')
else:
	print ('Rec nije prihvacena automatom')
 