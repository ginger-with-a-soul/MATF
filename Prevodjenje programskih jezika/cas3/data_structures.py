#! /usr/bin/python3
#import sys

a = (1, 2, 3, 4, 5)
al = list(a)

bl = [0, 2, 1, 4]
print(al + bl)

cl = ["String", 2, 2.1]
print(cl[0:2])

z = cl
z1 = z[:]
print(z, z1)

z[:0] = ("Na", "Pocetak")
z.extend(cl)
print(z)

z.remove("Na")
z.pop(1)
print(z)
print(z.index('String'))
print(z.count(2))

z.reverse()
print(z)