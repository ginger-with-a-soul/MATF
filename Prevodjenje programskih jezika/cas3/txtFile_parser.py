#! /usr/bin/python3
import sys
import re

if len(sys.argv) < 2:
    sys.exit("./txtFile_parser file.txt")

if re.match(r'.+\.txt', sys.argv[1], re.I) is None:
    sys.exit("File has to be textual")

try:
    f = open(sys.argv[1], "r")
except IOError:
    sys.exit(sys.argv[1] + " does not exist")

ri = re.compile(r'(?i)(\b[A-Za-z]+\b)\s+\1')

for line in f:
    match = ri.search(line)
    if match is not None:
        print("Match %s\t groups: %s" % (match.group(), match.groups()))
        print("Subbed regex parts: " + ri.sub("to change with", line))

f.close()