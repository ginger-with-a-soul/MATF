#! /usr/bin/env python
def kvadriraj(x):
    return x*x

def suma(x):
    return (x*(x+1)) // 2
    
def izbroj_neparne(lista):
    br = 0
    for i in lista:
        if lista[i] % 2 == 1:
            br += 1
    return br

def funkcija_lambda(f, x):
    return f(x)

def komparator(element):
    return (element[0], element[1])


def main():

    x = int(input("Unesite x: "))

    print("Kvadrirano: %d \nSuma: %d" % (kvadriraj(x), suma(x)))
    
    lista = range(0, 100)

    print("Neparnih je: %i" % (izbroj_neparne(lista)))

    print("F-ja lambda: %i" % (funkcija_lambda(lambda x: x*x*x, 2)))

if __name__ == "__main__":
    main()