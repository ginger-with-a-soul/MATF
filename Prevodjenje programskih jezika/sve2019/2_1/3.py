#!/usr/bin/python3

import sys

l = [1,2,3,4,5,6];
print(l)

t = (1, 2, 3, 4, 5, 6);
print(t)

#t[2] = 'neki string'
#print(t)

l[2] = "neki string"
print(l)

print(l[2:4])
print(l+l)
print(l*3)
print(l)

l[:0] = ["na", "pocetak"]
print(l)

print(l[:])

l1 = [1,2,3,4,5,6]

l.extend(l1)
print(l)

l.append(l1)
print(l)

print(l.count(2))

print(l.index(2))

l.remove(2)
print(l)

l = [1,2,3,4,5,6]
l.sort(reverse=True)
print(l)
l.reverse()
print(l)

l = ["na", "drvo", "matematika", "programiranje", "bod"]
l.sort(key = lambda x: len(x));
print(l)
