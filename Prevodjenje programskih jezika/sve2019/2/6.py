#!/usr/bin/python3

telefoni = {'Pera':123, 'Zika':239, 'Mika':187}

print(telefoni) 

print(telefoni.keys())
print(telefoni.values())

print(sorted(telefoni.values()))

print(telefoni.get("Laza"))

if telefoni.get('Laza') is None:
	print("Laza nije u imeniku")
	

if len(telefoni) < 3:
	print(telefoni);
else:
	telefoni["Laza"] = 500;
	
print(telefoni["Laza"])

parovi = zip(telefoni.keys(), telefoni.values())

for k,v in parovi:
	print(k,v)

for k in telefoni.keys():
	print(k, telefoni[k])
	
for k,v in telefoni.items():
	print(k,v)

a = 'abrakadabra'
b = ''

for c in a:
	if c == 'a':
		b = b + 'i'
	else:
		b = b + c

print(b)

