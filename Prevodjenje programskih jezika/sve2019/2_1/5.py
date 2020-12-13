#!/usr/bin/python3

import sys

s = input("Unesite broj:").split(" ")
#x = [];
#for ss in s:
#	x.append(int(ss))

x = map(int, s);
print(list(x))

if x%2 == 0:
	print("broj je paran")
	if (x > 100):
		print("Veci od 100")
	else:
		print("<= 100")
else:
	print ("Broj je neparan")
	if x % 3 == 0:
		print("Broj je deljiv sa tri")
	else:
		print("Broj nije deljiv sa tri")

