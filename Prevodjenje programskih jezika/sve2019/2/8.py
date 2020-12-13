#!/usr/bin/python3

import sys

if len(sys.argv) < 2:
	sys.exit("Argumenti")
	
for arg in sys.argv:
	print(arg)

try:
	f = open(sys.argv[1], "r");
except IOError:
	sys.exit("open")

for l in f:
	print(l, end="")
	
f.close()
