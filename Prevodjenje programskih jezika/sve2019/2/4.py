#!/usr/bin/python3

import sys

s = set('abrakadabra');
print(s)

b = ['abrakadabra', 'primer', 'primer'];

print(set(b))

if 'f' not in s:
	s.add('f')
	print("Slovo je dodato")
else:
	s.remove('f')
	print("Slovo je uklonjeno")
	
c = set('primer1234')

print(s)
print(c)

print(s&c)
print(s.intersection(c))

print(s|c)
print(s.union(c))

print(s-c)
print(s.difference(c))

print(s^c)
print(s.symmetric_difference(c))
	
