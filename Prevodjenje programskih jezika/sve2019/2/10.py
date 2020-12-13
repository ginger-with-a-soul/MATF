#!/usr/bin/python3

def prost(x = 2):
	if (x == 2):
		return 1
	
	if (x%2 == 0):
		return 2
	
	for i in range(3, x//2, 2):
		if (x % i == 0):
			return i
	
	return 1
	
try:
	x = int(input())
	if (x <= 1):
		raise ValueError
except ValueError:
	sys.exit("Unesite broj")
	
rezultat = prost(x);

if (rezultat == 1):
	print("Broj je prost")
else:
	print("%d = %d * %d"%(x, rezultat, x//rezultat))
