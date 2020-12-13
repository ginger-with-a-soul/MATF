#!/usr/bin/python3

import sys
import re

import os

if len(sys.argv) > 1:
	homedir = sys.argv[1]
else:
	homedir = '.'
	
re_dir = re.compile(r"^(m[mnvrlia]|a[aif])(0[5-9]|1[0-9])(00[1-9]|0[1-9]\d|[1-5]\d{2})$")
re_file = re.compile(r"^[1-9]\.(pas|c|cpp|java)$", re.I)

for f in os.listdir(homedir):
	dirPath = os.path.join(homedir, f)
	m = re_dir.match(f)
	if os.path.isdir(dirPath) and m is not None:
		print("\n" + m.group())
		for sf in os.listdir(dirPath):
			filePath = os.path.join(dirPath, sf)
			m = re_file.match(sf)
			if os.path.isfile(filePath) and m is not None:
				print("\t" + m.group())
	
