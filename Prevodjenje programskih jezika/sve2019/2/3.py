#!/usr/bin/python3

import sys

l = [1,2,3,4,5,6]
print(l)

t = (1,2,3,4,5,6)
print(t)

l[2] = "Neka rec";
print(l)

#t[2] = "Neka rec"

print(l[2])

print(l+l)
print(l*4)

print(l[2:5])

b = l[:]
print(b)

b[:0] = ['na', 'pocetak']
print(b)

b.extend(l)
print(b)

b.append('nesto')
print(b)

b.remove(2)
print(b)

print(b.index('nesto'))
print(b.count(2))

b.pop()
print(b)

b = [1,2,3,4,5,6]
b.sort(reverse=True)
print(b)

b.reverse()
print(b)

