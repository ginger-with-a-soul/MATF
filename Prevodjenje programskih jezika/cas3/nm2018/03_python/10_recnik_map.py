#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/
#
# Mapa je struktura podataka koja preslikava kljuceve u vrednosti.
# Naziva se cesto i recnik, i najcesce su implementacije preko
# balansiranih stabala pretrage kao i hes tabela.
#
# Mapa omogucava 3 operacije:
# - Ubacivanje vrednosti za dati kljuc
# - Pretragu vrednosti za dati kljuc
# - Uklanjanje vrednosti za dati kljuc

# --------------------------------------------------------------------------------
# Inicijalizacija mape
# --------------------------------------------------------------------------------
mapa = {"c++": 30, "java": 21, "javascript": 48}

# ili
mapa = {
    "python": 32,
    "c++": 30,
    "java": 21,
    "javascript": 48,
    "go": 13,
    "haskell": 10
}

# -------------------------------------------------------------------------------
# Mape mozemo konvertovati u string
# -------------------------------------------------------------------------------
# print(mapa)
# ili
print("Mapa: %s" % str(mapa))

# -------------------------------------------------------------------------------
# Citanje kljuca
# -------------------------------------------------------------------------------
broj_programa = mapa["python"]
print("Broj programa za jezik python je %d" % broj_programa)

# -------------------------------------------------------------------------------
# Menjanje vrednosti
# -------------------------------------------------------------------------------
mapa["python"] += 2
broj_programa = mapa["python"]
print("\nNakon menjanja, broj programa za jezik python je %d" % broj_programa)

# -------------------------------------------------------------------------------
# Provera da li za dati kljuc postoji vrednost
# -------------------------------------------------------------------------------
if "python" in mapa:
    print("\nMapa sadrzi vrednost za kljuc \"python\" i iznosi: %d" % mapa["python"])

# -------------------------------------------------------------------------------
# Sta ako trazimo vrednost za kljuc koji ne postoji?
# -------------------------------------------------------------------------------
# print(mapa["fortran"])
# -> Python izbacuje gresku/izuzetak 'KeyError' da kljuc "fortran" ne postoji.

# -------------------------------------------------------------------------------
# Nad mapom mozemo dobiti i skup kljuceva i skup vrednosti.
# -------------------------------------------------------------------------------
kljucevi = mapa.keys()
vrednosti = mapa.values()

# Metodi 'keys' i 'values' ne vracaju listu, vec posebne objektu koji
# predstavljaju 'pogled' na kljuceve i vrednosti.
print("\n")
print(kljucevi)
print(vrednosti)

# Ukoliko ih hocemo kao liste, mozemo ih proslediti konstruktoru 'list'
print("\n")
kljucevi = list(kljucevi)
vrednosti = list(vrednosti)
print(kljucevi)
print(vrednosti)

# Primetimo da menjanje listi, ne menja vrednosti u mapi
kljucevi[0] = "fortran"
vrednosti[0] = 100
print("\nMapa nakon menjanja listi kljuceva i vrednosti (nema promene): %s" % str(mapa))

# -------------------------------------------------------------------------------
# Iteriranje kroz mapu
# -------------------------------------------------------------------------------
# Koristimo metod 'items' koji vraca pogled na listu uredjenih parova
# oblika (kljuc, vrednost).
print("\nIteriranje kroz mapu:")
# Koristimo razmotavanje n-torki da direktno dobijemo kljuc i vrednost
for (k, v) in mapa.items():
    print("%s -> %s" % (str(k), str(v)))

# -------------------------------------------------------------------------------
# Bez razmotavanja n-torki
# -------------------------------------------------------------------------------
print("\nIteriranje kroz mapu (bez razmotavanje n-torke):")
for element in mapa.items():
    print("%s -> %s" % (str(element[0]), str(element[1])))


# -------------------------------------------------------------------------------
# Mapa dozvoljavaju da se bilo koji tip preslikava u bilo koji tip.
# -------------------------------------------------------------------------------
# Korisnici tipovi treba da implementiraju metod '__hash__' i '__eq__', no
# na ovom kursu nije u planu da implementiramo sopstvene tipove.
primer = {
    10: "zdravo",
    "zdravo": 10,
    100.111: 100.22222222,
    "string!": "i opet string!"
}
print("\nMapa sa razlicitim tipovima: %s" % str(primer))

# -------------------------------------------------------------------------------
# NAPOMENA
# -------------------------------------------------------------------------------
# Pretpostavimo da mapa ima 'n' elemenata, dakle 'n' kljuceva koji
# se slikaju u 'n' vrednosti, i pretpostavimo da je mapa implementirana
# kao balansirano stablo pretrage.
#
# Analizirajmo sledeci nacin da se iterira kroz mapu
print("\nNeefikasno iteriranje kroz mapu")
for k in mapa.keys():
    print("%s -> %s" % (k, mapa[k]))
# Koja je slozenost izlozenog koda?
# Za 'n' kljuceva, radimo operaciju slozenosti O(log n) te
# dobijamo slozenost O(n log n), drasticno vece u odnosu na
# O(n) kada se koristi metod 'items'.
