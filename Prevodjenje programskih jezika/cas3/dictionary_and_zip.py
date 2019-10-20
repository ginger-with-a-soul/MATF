#! /usr/bin/python3
import sys

dict = {"Dimi" : 0, "Joca" : 3, "Tomo" : 11, "Djape" : 4}

print(dict["Dimi"])
print(dict.get('Dima'))

print(dict.keys())

if len(dict) < 3:
    print(dict)
elif "Comi" not in dict.keys():
    dict["Comi"] = 10
    print("Comi added to dictrionary")
else:
    print(dict["Comi"])

print(dict)

print(("Dimi", 0) in zip(dict.keys(), dict.values()))
print(("Djape", 2) in zip(dict.keys(), dict.values()))

for k in dict.keys():
    print(k, dict[k])

for k, v in dict.items():
    print(k, v)

a = "abrakadabra"
b = ""

for x in a:
    if x == 'a':
        b += 'e'
    else:
        b += x
print(b)

for i in range(1, 11, 2):
    print(i ** 2)

l = ["Neka", "lista", "stringova"]

for i in l:
    print(i)

for i in l[:]:
    l.insert(len(l) - 1, i)

print(l)


