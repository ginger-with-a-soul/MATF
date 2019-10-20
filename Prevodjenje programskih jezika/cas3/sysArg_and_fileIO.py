#! /usr/bin/python3
import sys

print(sys.argv)

if len(sys.argv) < 2:
    print("Invalid arg count")
else:
    try:
        f = open(sys.argv[1], "r")
    except IOError:
        sys.exit("Invalid arg[1]")


for l in f:
    print(l)

f.close()