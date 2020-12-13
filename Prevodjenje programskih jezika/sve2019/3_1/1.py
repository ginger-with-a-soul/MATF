#!/usr/bin/python3

import sys
import re

if len(sys.argv) < 2:
	sys.exit("argumenti")
	
if re.match(r"^.+\.txt$", sys.argv[1], re.I) is None:
	sys.exit("ekstenzija")
	
try:
	f = open(sys.argv[1], "r")
except IOError:
	sys.exit("fajl ne postoji")

ri = re.compile(r"(\b[a-zA-Z]+\b)\s+\1");

for linija in f:
	m = ri.search(linija)
	if m is not None:
		#print(m.group(1))
		print("Poklapanje: %s\tgrupe: %s"%(m.group(), m.groups()))
		print("Linija bez ponavljanja: " + ri.sub('bilo sta', linija))
	
f.close();


try:
	with open(sys.argv[1], "r") as f:
		podaci = f.read()
except IOError:
	sys.exit("fajl ne postoji")
	
for m in ri.finditer(podaci):
	print(m.group())
