#!/usr/bin/python3

import sys
import re

if len(sys.argv) < 2:
	sys.exit("argumenti")
	
if re.match(r"^.+\.txt$", sys.argv[1], re.I) is None:
	sys.exit("ekstenzija")
	
ri = re.compile(r"(\b[a-zA-Z]+\b)\s+\1");

try:
	f = open(sys.argv[1], "r")
except IOError:
	sys.exit("open")
	
for linija in f:
	match = ri.search(linija)
	if match is not None:
		print ("Poklapanje: %s\n groups: %s"%(match.group(), match.groups()))
		print ("Linija bez ponavljanja: " + ri.sub('bilo sta', linija))
		
f.close()

try:
	f = open(sys.argv[1],"r")
	data = f.read();
except IOError:
	sys.exit("....")
	
for m in re.finditer(r"(\b[a-zA-Z]+\b)\s+\1", data, re.I):
	print(m.group())
	
f.close()
