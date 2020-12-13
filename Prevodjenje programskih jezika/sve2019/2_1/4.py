#!/usr/bin/python3

import sys

s = set("abrakadabra");
print(s)


b = ["abrakadabra", "primer", "primer"]
b = set(b)

print(b)

if 'f' not in s:
	s.add('f')
	print("Ubaceno novo slovo f")
else:
	s.remove('f')
	print("Izbaceno slovo f")


print(s)
c = set("primer1234")

print(s&c)
print(s.intersection(c))

print(s|c)
print(s.union(c))

print(s-c)
print(s.difference(c))

print(s^c)
print(s.symmetric_difference(c))
