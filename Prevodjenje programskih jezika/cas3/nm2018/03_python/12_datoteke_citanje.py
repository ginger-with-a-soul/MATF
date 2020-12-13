#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/

import sys

def procitaj_datoteku(putanja):
    try:
        # Ukoliko koristimo ovu konstrukciju, nije nam neophodno zatvaranje datoteke,
        # python sam to cini nakon isteka 'with' bloka.
        with open(putanja, "r") as f:
            podaci = []
            # Citamo liniju po liniju
            for linija in f:
                tokeni = linija.split(",")
                jezik = tokeni[0]
                godina = int(tokeni[1])
                # Dodajemo uredjeni par u listu
                podaci.append((jezik, godina))
            return podaci

            # celokupan sadrzaj datoteke smo mogli procitati sa:
            # data = f.read()   # funkcija vraca string koji predstavlja sadrzaj datoteke

    except IOError:
        return None

def procitaj_datoteku_drugi_nacin(putanja):
    try:
        # Pokusavamo da procitamo datoteku
        f = open(filename, "r")
        podaci = []
        # Citamo sadrzaj datoteke liniju po liniju:
        for linija in f:
            # Razbijamo liniju na niz stringova,
            tokeni = linija.split(",")
            jezik = tokeni[0]
            godina = int(tokeni[1])
            # Dodajemo uredjeni par u listu
            podaci.append((jezik, godina))

        # Zatvaramo datoteku
        f.close()
        return podaci

    except IOError:
        # Ukoliko ne uspe citanje, ispaljuje se izuzetak IOError koji hvatamo i obradjujemo
        return None


# Citamo podatke
podaci = procitaj_datoteku("09_input.csv");
if podaci == None:
    print("Neuspelo citanje datoteke!")
    sys.exit(1)

# Trazimo najstariji jezik
mini = podaci[0][1]
jezik = podaci[0][0]
for par in podaci:
    if par[1] < mini:
        jezik = par[0]
        mini = par[1]

print("Najstariji jezik: %s %d" % (jezik, mini))
