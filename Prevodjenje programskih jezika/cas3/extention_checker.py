#! /usr/bin/python3
import sys
import re

if len(sys.argv) < 2:
    sys.exit("Invalid argv count")

ext = re.match(r'.+\.txt', sys.argv[1], re.I)

if ext is None:
    sys.exit("Extention has to be .txt")
else:
    print(sys.argv[1])