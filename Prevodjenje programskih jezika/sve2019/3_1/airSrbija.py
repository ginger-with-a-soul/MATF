#!/usr/bin/python3

import re
import sys

if len(sys.argv) < 2:
	sys.exit("greska")
	
if re.match(r"^.*\.txt$", sys.argv[1], re.I) is None:
	sys.exit("greska")
	
try:
	with open(sys.argv[1], "r") as f:
		podaci = f.read();
except IOError:
	sys.exit("greska")
	
ri = re.compile(r"{(.*?),\.NE\+([a-z]+):[0-9][a-z]}", re.S);

zamenjen = ri.sub(r"<\2>\1</\2>", podaci);

try:
	with open("rezultat.xml", "w") as f:
		f.write("<xml>\n");
		f.write(zamenjen);
		f.write("\n</xml>\n");
except IOError:
	sys.exit("greska");
