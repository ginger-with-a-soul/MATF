#!/usr/bin/python3

import sys
import re

#if len(sys.argv) < 2:
#	sys.exit("Argumenti")
	
try:
	with open("knjige.xml", "r") as f:
			podaci = f.read();
except IOError:
	sys.exit("fajl ne postoji")
	
ri = re.compile(r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[0-9]+)"\s*>\s*'
+r"(?=.*?<naslov>\s*(?P<naslov>.+?)\s*</naslov>)"
+r"(?=.*?<autor>\s*(?P<autor>[A-Z][a-z]+(\s+[A-Z][a-z]+)+)\s*</autor>)"
+r"(?=.*?<godina_izdanja>\s*(?P<godina>[0-9]{4})\s*</godina_izdanja>)"
+r"(?=.*?<izdavac>\s*(?P<izdavac>.+?)\s*</izdavac>)"
+r'(?=.*?<cena\s+valuta\s*=\s*"(?P<valuta>[a-z]{3})"\s*>\s*(?P<cena>[1-9][0-9]*)\s*</cena>)'
+r'.*?'
+r"</knjiga>",re.S);

biblioteka = {}

for m in ri.finditer(podaci):
	m1 = re.match(r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[0-9]+)"\s*>\s*'
		+r"(?=.*?<naslov>\s*(?P<naslov>.+?)\s*</naslov>)"
		+r"(?=.*?<autor>\s*(?P<autor>[A-Z][a-z]+(\s+[A-Z][a-z]+)+)\s*</autor>)"
		+r"(?=.*?<godina_izdanja>\s*(?P<godina>[0-9]{4})\s*</godina_izdanja>)"
		+r"(?=.*?<izdavac>\s*(?P<izdavac>.+?)\s*</izdavac>)"
		+r'(?=.*?<cena\s+valuta\s*=\s*"(?P<valuta>[a-z]{3})"\s*>\s*(?P<cena>[1-9][0-9]*)\s*</cena>)'
		+r'.*?'
		+r"</knjiga>", m.group(), re.S)
	if m1 is not None:
		biblioteka[m.group('rbr')] = [m.group('autor'),m.group('naslov'), 
								m.group('godina'), m.group('izdavac'),
								m.group('valuta'), m.group('cena')];

for k,v in biblioteka.items():
	print(k, v, sep=" : ")


