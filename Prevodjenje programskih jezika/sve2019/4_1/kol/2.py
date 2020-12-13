#!/usr/bin/python3

import sys

stanje = 'A'
zavrsna = ['D', 'E']

prelazi = {	('A', '0') : 'B', ('A', '1') : 'C',
			('B', '0') : 'D', ('B', '1') : 'C',
			('C', '0') : 'B', ('C', '1') : 'E',
			('D', '0') : 'D', ('D', '1') : 'C',
			('E', '0') : 'B', ('E', '1') : 'E',
		}

while True:
	try:
		c = input();
	
		if c != '0' and c != '1':
			raise ValueError("pogresan format")
	except ValueError as e:
		sys.exit(e)
	except EOFError:
		break;
		
	stanje = prelazi[(stanje, c)]
	
if stanje in zavrsna:
	print("Automat prihvata rec")
else:
	print("Automat ne prihvata rec")
	
	
(a|c)*b+c*
