#! /usr/bin/python3
import sys

s = set("HelloSet")
bl = ["This", "is", "a", "list"]

bs = set(bl)
print(s, bs)

x = {"A", "set", "A", "list"}
print(x)

print(x & bs)
print(x | bs)
print(x - bs)
print(x ^ bs)

if not 's' in s:
    s.add('s')
    print("s is added to s")
else:
    s.remove('s')
    print("s is removed from s")