#!/usr/bin/python3

import sys
import re

if len(sys.argv) < 2:
	sys.exit("argumenti")

if re.match(r"^.+\.html$", sys.argv[1], re.I) is None:
	sys.exit("ekstenzija")
	
try:
	with open(sys.argv[1], "r") as f:
		podaci = f.read();
except IOError:
	sys.exit("fajl ne postoji")
	
ri = re.compile(r"<tr>"
+r"\s*<td>\s*(?P<ime>[A-Z][a-z]+(\s+[A-Z][a-z]+)+)\s*</td>"
+r"\s*<td>\s*(?P<prakticni>[0-9]|[1-9]\d|100)\s*</td>"
+r"\s*<td>\s*(?P<teorija>[0-9]|[1-9]\d|100)\s*</td>"
+r"\s*</tr>", re.S);

studenti = []
poeni = []

for m in ri.finditer(podaci):
	ime = m.group('ime');
	prakticni = int(m.group('prakticni'))
	teorija = int(m.group('teorija'))
	studenti.append(ime)
	poeni.append((prakticni+teorija)/2)
	
parovi = sorted(zip(poeni, studenti))
parovi.reverse()

for p,s in parovi:
	print(s, p)

