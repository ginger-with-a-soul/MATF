#!/usr/bin/python3

import sys
import re

poruka = "Danas je divan dan"
m = re.match(r'(?i)(\w+\s*)+', poruka)

if m is None:
	print("Nema reci")
else:
	print(m.group())

m = re.search(r'\bd([a-z]+)', poruka)

if m is not None:
	print(m.group(), m.groups())
	print(poruka[m.start():m.end()])
	
m = re.search(r'\bd([a-z]+)', poruka[m.end(): ])
if m is not None:
	print(m.group())
	
	
reci = re.findall(r'\b(d([a-z]+))', poruka, re.I)
print(reci)

print(re.sub(r'(?i)\b(d([a-z]+))', r'\2-\1', poruka))
print(poruka.replace('Danas', 'Sutra'))
