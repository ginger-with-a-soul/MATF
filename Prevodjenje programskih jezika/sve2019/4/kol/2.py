#!/usr/bin/python3

import sys

stanje = 'A'
zavrsna = ['D', 'E']

prelazi = {('A', '0'):'B', ('A', '1'):'C',
			('B', '0'):'D', ('B', '1'):'C',
			('C', '0'):'B', ('C', '1'):'E',
			('D', '0'):'D', ('D', '1'):'C',
			('E', '0'):'C', ('E', '1'):'E',
		}
		
while True:
	try:
		c = input();
	except EOFError:
		break;
	
	if prelazi.get((stanje, c)) is not None:
		stanje = prelazi[(stanje, c)]
	else:
		sys.exit("rec nije deo jezika")
		
if stanje in zavrsna:
	print("Automat prihvata rec")
else:
	print("automat ne prihvate rec")
