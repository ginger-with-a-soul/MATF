#!/usr/bin/python3

import sys
import re

def obradi_stranice(data):
	
	if data in obradjene_stranice:
		return;
	
	obradjene_stranice.append(data)
	
	try:
		with open(data, "r") as f:
			podaci = f.read()
	except IOError:
		sys.exit("fajl ne postoji")
		
	ri = re.compile(r'<a\s*href\s*=\s*"(?P<url>([^"]+?))"\s*>.*?</a>', re.I);
	
	for m in ri.finditer(podaci):
		url = m.group('url')
		
		if url in statistika:
			statistika[url] += 1
		else:
			statistika[url] = 1
			
		obradi_stranice(url)
		

if len(sys.argv) < 2:
	sys.exit("argumenti");
	
if re.match(r"^.*\.html$", sys.argv[1], re.I) is None:
	sys.exit("ekstenzija")
	
	
obradjene_stranice = []
statistika = {}

obradi_stranice(sys.argv[1])

parovi = sorted(zip(statistika.values(), statistika.keys()));
parovi.reverse();

for p,i in parovi:
	print(ime, posete, " : ")

