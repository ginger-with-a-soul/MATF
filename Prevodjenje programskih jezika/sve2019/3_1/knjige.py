#!/usr/bin/python3

import sys
import re

autor = False
izdavac = False
cena = False
godina = False

if len(sys.argv)<2:
	sys.exit("Argumenti")
	
if len(sys.argv) == 2:
	knjiga = sys.argv[1];
elif len(sys.argv) == 3:
	knjiga = sys.argv[2]
	opcije = sys.argv[1]
	
	for c in opcije:
		if c == 'a':
			autor = True
		elif c == 'i':
			izdavac = True
		elif c == 'g':
			godina = True;
		elif c == 'c':
			cena = True
	
else:
	sys.exit("Neodgovarajuce opcije")

try:
	with open("knjige.xml", "r") as f:
		podaci = f.read()
except IOError:
	sys.exit("Fajl ne postoji")
	
	
ri_knjige = re.compile(r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[0-9]+)"\s*>.*?</knjiga>', re.S);
	
ri = re.compile(r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[0-9]+)"\s*>'
+ r'\s*(?=.*?<naslov>\s*(?P<naslov>.+?)\s*</naslov>)'
+ r'\s*(?=.*?<autor>\s*(?P<autor>[^<]+?)\s*</autor>)'
+ r'\s*(?=.*?<izdavac>\s*(?P<izdavac>.*?)\s*</izdavac>)'
+ r'\s*(?=.*?<godina_izdanja>\s*(?P<godina>\d{4})\s*</godina_izdanja>)'
+ r'\s*(?=.*?<cena\s+valuta\s*=\s*"(?P<valuta>[a-z]{3})"\s*>\s*(?P<cena>[1-9][0-9]*)\s*</cena>)'
+ r".*?"
+ r"\s*</knjiga>", re.S);

biblioteka = {}

for m in ri_knjige.finditer(podaci):
	m1 = ri.match(m.group());
	if m1 is not None:
		biblioteka[m1.group('rbr')] = [m1.group('autor'),m1.group('naslov'),m1.group('izdavac'), m1.group('godina'), m1.group('valuta'), m1.group('cena')]
		

info = None;	
for k,v in biblioteka.items():
	if (v[1] == knjiga):
		info = v;
	
if info is None:
	print("nema knjige")
	sys.exit()
	
if not (autor and godina and izdavac and cena):
	print(info)
	sys.exit()
	
if autor:
	print(v[0])
if izdavac:
	print(v[2])
if godina:
	print(v[3])
if cena:
	print(str(v[5])+v[4])
