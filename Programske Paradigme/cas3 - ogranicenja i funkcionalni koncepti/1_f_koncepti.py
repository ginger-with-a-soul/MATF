import string
from functools import reduce

#1. zadatak

x, y = input("Enter x and y: ").split()

a, b, c, d = input("Enter a, b, c, d: ").split()


def make_pairs(a, b, c, d, i, j):
    return [(i, j) for i in range(a, b + 1) for j in range(c, d + 1)]

lista = make_pairs(int(a), int(b), int(c), int(d), int(x), int(y))
print(lista)

#2. zadatak

n = int(input("Insert number of students: "))
names = [input(f"Insert name number {i + 1}: ") for i in range(n)]
grades = [input(f'Insert average grade for {names[i]}: ') for i in range(n)]

zipped = zip(names, grades)

for pair in zipped:
    print(pair)

#3. zadatak

someString = str(input("Insert some string: "))

print(''.join(list(map(lambda c: c.upper(), someString))))

#4. zadatak

someOtherString = str(input("Insert some other string: "))

print(list(filter(lambda c: not c.isalpha(), someOtherString)))

#5. zadatak
n2 = 0

try:
    n2 = int(input("Insert n >= 0: "))
except ValueError as err:
    print(err)

numbers = range(0, n2 + 1)

print(f'Sum of first {n2} is: {reduce(lambda x, y: x + y, numbers)}')