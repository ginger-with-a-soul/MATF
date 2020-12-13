#!/usr/bin/python3

import sys
import re

if len(sys.argv) < 2:
	sys.exit("argumenti")

try:
	with open("paket.xml","r") as f:
		podaci = f.read();
except IOError:
	sys.exit("Fajl ne postoji")
	
paket_ri = re.compile(r"<paket\s+id\s*=\s*\"[0-9]+\"\s*>.*?</paket>", re.S)
valid_ri = re.compile(r'<paket\s+id\s*=\s*"(?P<id>[0-9]+)"\s*>\s*'
+ r"(?=.*?<naziv>\s*(?P<naziv>[a-zA-Z]+)\s*</naziv>\s*)"
+ r"(?=.*?<verzija>\s*(?P<verzija>[0-9]+\.[0-9]+\.[0-9]+)\s*</verzija>\s*)"
+ r"(?=.*?<opis>\s*(?P<opis>[a-zA-Z .]+)\s*</opis>\s*)"
+ r"(?=.*?<repo>\s*(?P<repo>gitlab|github|bitbucket)\s*</repo>\s*)"
+ r"(?=.*?<veb>\s*(?P<veb>(www\.)?([a-zA-Z]+\.)+(org|com))\s*</veb>\s*)"
+ r".*?"
+ r"</paket>"
, re.S)

paketi = {}

for p in paket_ri.finditer(podaci):
	m = valid_ri.match(p.group())
	if m is not None:
		#print(m.group())
		paketi[m.group("naziv")] = [m.group("id"), m.group("verzija"), m.group("opis"), m.group("repo"), m.group("veb")]
		
if len(sys.argv) == 2:
	if sys.argv[1] == '-a':
		parovi = sorted(zip(paketi.keys(), paketi.values()))
		for k,v in parovi:
			print(k, v, sep=":")
	else:
		sys.exit("Pogresna opcija")
elif len(sys.argv) == 3:
	if sys.argv[1] == "-v":
		if paketi.get(sys.argv[2]) is not None:
			print(paketi[sys.argv[2]][1])
		else:
			print("Ne postoji ta paket")
	elif sys.argv[1] == "-w":
		if paketi.get(sys.argv[2]) is not None:
			print(paketi[sys.argv[2]][4])
		else:
			print("Ne postoji ta paket")
	elif sys.argv[1] == "-r":
		if paketi.get(sys.argv[2]) is not None:
			print(paketi[sys.argv[2]][3])
		else:
			print("Ne postoji ta paket")
	elif sys.argv[1] == "-o":
		if paketi.get(sys.argv[2]) is not None:
			print(paketi[sys.argv[2]][2])
		else:
			print("Ne postoji ta paket")
	else:
		sys.exit("Nepostojeca opcija")

