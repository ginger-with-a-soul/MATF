#!/usr/bin/python3

import sys

stanje = 'AC'
zavrsno = 'E'

prelazi = {	('AC', 'a') : 'B',
			('AC', 'b') : 'AC',
			('B', 'a') : 'B',
			('B', 'b') : 'D',
			('D', 'a') : 'B',
			('D', 'b') : 'E',
			('E', 'a') : 'B',
			('E', 'b') : 'AC',
			}

while True:
	
	try:
		c = input()
		if (c != 'a' and c != 'b'):
			raise ValueError("samo 0 i 1")
	except EOFError:
		break;
	except ValueError as e:
		sys.exit(e)
	
	if prelazi.get((stanje, c)) is not None:
		stanje = prelazi[(stanje, c)]
	else:
		sys.exit("Automat ne prihvate rec")
		
if stanje == zavrsno:
	print("paran broj 0")
else:
	print("Neparan broj 0")
	
