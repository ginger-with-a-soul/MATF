#!/usr/bin/python3

s = input("Unesite broj: \n")
print(s)


m = map(int, s.split(" "))
print(m)

for x in m:
	if x%2 == 0:
		print("Broj je paran")
		if (x > 1000):
			print("Broj je veci od 1000")
		else :
			print("Broj je <= 1000")
	else:
		print("Broj je neparan")
		if x % 3 == 0:
			print("Broj je deljiv sa 3")
		else:
			print("Broj nije deljiv sa tri")
