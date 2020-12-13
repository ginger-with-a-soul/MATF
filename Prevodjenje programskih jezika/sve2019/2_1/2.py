#!/usr/bin/python3

import sys

s = 'Hello "world"'

#s[2] = 'L'

print(s)
print(s+s)
print(s*3)

x = 5
y = 3
print(x, y, sep=" razmak ")
print(x, end=" ")
print(y)

print(s[2])
print(s[2:5])
print(s[:5])
print(s[2:])

#  H   e   l   l   o
#  0   1   2   3   4
# -5  -4  -3  -2  -1

print(s[10:5])

print(len(s))
