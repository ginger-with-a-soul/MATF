#!/usr/bin/python

import sys
import re

if len(sys.argv) < 2:
	sys.exit("argumenti")

if re.match(r"^.+\.html$", sys.argv[1], re.I) is None:
	sys.exit("ekstenzija")
	
try:
	with open(sys.argv[1], "r") as f:
		podaci = f.read()
except IOError:
	sys.exit("fajl ne postoji")

ri = re.compile(r"<tr>" 
+ r"\s*<td>\s*(?P<ime>[A-Z][a-z]+(\s+[A-Z][a-z]+)+)\s*</td>"
+ r"\s*<td>\s*(?P<prakticni>\d|[1-9]\d|100)\s*</td>"
+ r"\s*<td>\s*(?P<teorija>\d|[1-9]\d|100)\s*</td>"
+ r"\s*</tr>", re.S)

studenti = []
poeni = []

#m = ri.search(podaci)

#while m is not None:
#	studenti.append(m.group('ime'));
#	ukupno = (int(m.group('prakticni')) + int(m.group('teorija')))/2
#	poeni.append(ukupno)
#	
#	m = ri.search(podaci, m.end())

for m in ri.finditer(podaci):
	studenti.append(m.group('ime'))
	ukupno = (int(m.group('prakticni')) + int(m.group('teorija')))/2
	poeni.append(ukupno)

parovi = sorted(zip(poeni, studenti))
parovi.reverse()
for p,s in parovi:
	print(s, p)
