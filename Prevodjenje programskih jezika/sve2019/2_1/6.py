#!/usr/bin/python3

import sys

telefoni = {"Pera": 100, "Zika":200,"Mika":300}

print(telefoni)

print(telefoni.keys())
print(telefoni.values())

#for k in telefoni.keys():
#	print(k, telefoni[k])

#parovi = zip(telefoni.keys(), telefoni.values())
#for k,v in parovi:
#	print(k,v)

for k,v in telefoni.items():
	print(k,v)

if telefoni.get("Laza") is None:
	print("Laza nije u imeniku")
else:
	print("Laza je u imeniku")
	


if len(telefoni) < 3:
	print(telefoni)
else:
	telefoni["Laza"] = 500;
	print("Ubacen novi korisnik")

print(telefoni["Laza"])

a = "abrakadabra"
b = ""

for c in a:
	if c == 'a':
		b = b + 'i'
	else:
		b =  b + c
		
print(b)

