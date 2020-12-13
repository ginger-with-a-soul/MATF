#!/usr/bin/python3

import sys

# pravimo ntorku (tupple)
# ntorka je nepromenljiva lista 
a = 1,2,3,4,5,6
# stampanje ntorke je moguce direktno. U terminologiji jave
# svaka kolekcija ima predefinisan toString() metod
print(a)

# pravimo listu od ntorka a
l = list(a)
# stampamo je na isti nacin
print(l)

b = (1,2,3,4,5,6)	# tupple se eksplicitno definise obicnim zagradama
lb = [1,2,3,4,5,6]  # lista se eksplicitno definise uglastim zagradama

# BITNO:
# tupple je read-only lista i bilo koji pokusaj promene elemenata je automatski
# greska u programu
# BITNO 2:
# i lista i tupple ne zahtevaju da svi elementi budu istog tipa, vec su proizvoljne kolekcije

print ("Tupple ", b)
print ("Lista ", lb)

# i lista i tupple podrzavaju indeksni pristup. indeksiranje krece od 0
print (b[3])
# u listama je moguca promena elemenata proizvoljnim vrednostima
lb[3] = 10
# stampanje liste
print (lb)
# stmapanje liste nadovezane na samu sebe
print (lb*2)

# nadovezivanje listi
# BITNO: liste l i lb ne menjaju, vec nastaje novi objekat
c = l + lb
print (c)

# stampanje ntorke nadovezane samu na sebe
print (a*2)

# i liste i tupplovi podrzavaju indeksirani pristup kao u slucaju nizova
# stampaju se drugi i treci element liste
# BITNO: stampaju se elementi na pozicijama 1 i 2, dok se element na poziciji 3 ne stampa
print (lb[1:3])

# lista je kolekcija proizvoljnih tipova
l = [1,2, '3', 'tajfun', 8.876]
print (l)

# pravljenje kopije
b = l[:]
print (b)

# dodavanje elemenata na pocetak liste
b[:0] = ['na', 'pocetak']
print (b)

# Extend metod nadovezuje sadrzaj liste l na listu b
# BITNO: lista b se menja u mestu.
b.extend(l)
print (b)

# Append metod dodaje element na kraj liste. Element moze da bude bilo kog tipa, cak
# i druga lista
# BITNO: lista b se menja u mestu
b.append('uragan')
print (b)

# metod remove uklanja prvu pojavu broja 2 u listi
b.remove(2)
print (b)

# metod pop uklanja poslednji element koji je ubacen u listu. (radi kao stek)
print (b.pop())
print (b)

# metod pop sa argumentom uklanja element bas na toj poziciji
print (b.pop(0))
print (b)

# sortiranje liste u mestu.
# python3 podrzava sortiranje i pomocu metoda sorted
# b1 = sorted(b)
b.sort()
print (b)

# okretanje liste u mestu
b.reverse()
print (b)

# metod index vraca indeks prvog pojavljivanja prosledjenog elementa
print (b.index('pocetak'))

# metod count vraca ukupan broj pojavljivanja prosledjenog elementa
print (b.count('tajfun'))

