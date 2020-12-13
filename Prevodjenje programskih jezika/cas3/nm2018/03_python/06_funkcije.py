#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/


def kvadriraj(x):
    return x*x

def suma_prvih_n(n):
    return (n*(n+1)) // 2

def izbroj_neparne(lista):
    brojac = 0
    for x in lista:
        if x % 2 != 0:
            brojac += 1
    return brojac

n = int(input("Unesite ceo broj: "))
print("%d^2 = %d" % (n, n*n))
print("n = %d zbir = %d" % (n, suma_prvih_n(n)))

# Range prave objekat klase 'range'
tmp = range(1, 100)

# Lista se moze konstruisati od objekta klase 'range'.
ls = list(range(1, 100))
print("%s neparni: %d" % (tmp, izbroj_neparne(ls)))

# -------------------------------------------------------------------------------
# Zabavno :)
# -------------------------------------------------------------------------------
# Python dozvoljava i da pravimo 'anonimne' funkcije, takozvane 'lambde'.
# Na primer:
# Pravimo funkciju koja primenjuje funkciju 'f' na element 'x' i potom
# vraca rezultat.
def primeni_funkciju(f, x):
    return f(x)

kvadrirana_cetvorka1 = primeni_funkciju(lambda x: x*x, 2)
kvadrirana_cetvorka2 = primeni_funkciju(kvadriraj, 2)
print("4^2 = %d" % kvadrirana_cetvorka1)
print("4^2 = %d" % kvadrirana_cetvorka2)

# Zapravo mozemo uraditi ovako nesto
# Pravimo anonimnu funkciju, potom joj dodeljujemo ime.
kvadriraj = lambda x: x*x
# Promenljiva 'kvadriraj' sada referise na funkciju nad kojom
# mozemo primeniti operator ()
print("10^2 = %d" % kvadriraj(10))

# -------------------------------------------------------------------------------
# Sortiranje
# -------------------------------------------------------------------------------
# Lambde su nam cesto bitne kod sortiranja jer njima mozemo
# definisati kako algoritam da vrsi poredjenja.
tacke = [(1, 2), (10, 2), (-1, 10), (-1, 22), (-1, 110), (41, 21), (42, 42)]

def comparator(element):
    return (element[0], element[1])

sortirane_tacke = sorted(tacke, key=comparator)

# element -> element liste
# (x, y) -> razmotavamo n-torku
# lambda element: (element[0], element[1]) -> sortiraj listu, prvo poredi x koordinatu,
# a potom y ukoliko ima potrebe
sortirane_tacke = sorted(tacke, key=lambda element: (element[0], element[1]))
print(sortirane_tacke)
