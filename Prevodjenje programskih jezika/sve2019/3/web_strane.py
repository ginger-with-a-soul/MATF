#!/usr/bin/python3

import sys
import re

def obradi_datoteke(dat):
	
	if dat in obradjene_datoteke:
		return
		
	obradjene_datoteke.append(dat)
	
	try:
		with open(dat, "r") as f:
			podaci = f.read();
	except IOError:
		sys.exit("fajl ne postoji")
		
	ri = re.compile(r'<a\s+href\s*=\s*"([^"]+)"\s*>(.*?)</a>',re.S|re.I);
	
	for m in ri.finditer(podaci):
		url = m.group(1)
		ime = m.group(2)
		
		if url in statistika:
			statistika[url] += 1
		else:
			statistika[url] = 1
			
		obradi_datoteke(url)

if len(sys.argv) < 2:
	sys.exit("argumenti")
	
if re.match(r"^.+\.html$", sys.argv[1], re.I) is None:
	sys.exit("ekstenzija")
	
obradjene_datoteke = []
statistika = {}

obradi_datoteke(sys.argv[1])

parovi = sorted(zip(statistika.values(), statistika.keys()))
parovi.reverse()

for v,s in parovi:
	print(s,v, sep=":")

