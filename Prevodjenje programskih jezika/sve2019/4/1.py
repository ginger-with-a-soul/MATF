#!/usr/bin/python3

import sys

broj_nula = 0;

while True:
	try:
		c = input("Unesite nula ili jedan")
		if (c != '0' and c != '1'):
			raise ValueError("pogresna vrednost")
	except ValueError as e:
		print(e)
		sys.exit()
	except EOFError:
		break;
		
	if c == '0':
		broj_nula+=1;
		
if (broj_nula % 2 == 0):
	print("Unet je paran broj nula")
else:
	print("Unet je neparan borj nula")
