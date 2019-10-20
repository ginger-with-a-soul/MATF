#! /usr/bin/python3
import sys

x = int(input("Input a number: "))

print(x / 3)
print(x % 3)
print(x // 3)

if x > 1000:
    print("Number greater than 1000")
else:
    if x % 2:
        print("It's an odd number")
    else:
        print("It's an even number")
    print("Number smaller or equal to 1000")

print("Block of code is determined by tab indentation!")