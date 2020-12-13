#!/usr/bin/python3

import sys
import re

if len(sys.argv) < 2:
	sys.exit("argumenti")
	
match = re.match(r'^.+\.txt$', sys.argv[1], re.I);

if match is None:
	sys.exit("ekstenzija")
else:
	print("Sve je ok");
