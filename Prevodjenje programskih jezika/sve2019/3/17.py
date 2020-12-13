#!/usr/bin/python3

import sys
import re

poruka = "Danas je divan dan"
match = re.match(r"(?i)(\w+\s+)(\w+\s+)*", poruka)

if match is not None:
	print(match.groups())
else:
	print("Nema poklapanja")
	
m = re.search(r"\bd([a-z]+)", poruka, re.I)

if m is not None:
	print(m.group())	
	print(poruka[m.start():m.end()])
	
m = re.search(r"\bd([a-z]+)", poruka[m.end()-1:])
if m is not None:
	print(m.group())	
	
m = re.findall(r"\b(d([a-z]+))", poruka)
print(m)

print(poruka.replace('Danas','Sutra'))

	


