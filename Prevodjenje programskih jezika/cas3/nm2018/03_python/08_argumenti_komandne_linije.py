#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/
# Primer rada sa argumentima komandne linije.
# Program sumira prosledjene brojeve i ispisuje njihov zbir na standardni izlaz.

import sys

# sys.argv je lista argumenata koji su prosledjeni programu ukljucujuci
# ime programa. Tip elemenata u listi je string.

if len(sys.argv) == 1:
    print(0)
    sys.exit(0)

# Odbacujemo 0-ti element, ne treba nam ime programa.
args = sys.argv[1:]

suma = 0
for arg in args:
    suma += int(arg)
print("suma = %d" % suma)
