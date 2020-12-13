#!/usr/bin/python3

import sys
import re

if len(sys.argv) < 2:
	sys.exit("argumenti")
	
match = re.match(r'^.+\.txt$', sys.argv[1], re.I);

if match is None:
	print("Ekstenzija ne valja")
else:
	print("Sve ok")


#print(r"Hello world\n")

#print(""" Ovo je
#viselinijski
#string""");
