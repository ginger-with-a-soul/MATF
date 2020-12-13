#! /usr/bin/env python
# -*- coding: utf-8 -*-
#              _   _                 _____
#  _ __  _   _| |_| |__   ___  _ __ |___ /
# | '_ \| | | | __| '_ \ / _ \| '_ \  |_ \
# | |_) | |_| | |_| | | | (_) | | | |___) |
# | .__/ \__, |\__|_| |_|\___/|_| |_|____/
# |_|    |___/

# Formatiranje teksta

a = 10
# Nacin 1 (nad stringom pozivamo metod .format)
# Argumenti metoda format se unifikuju redom sa elementima {} u stringu.
print("a = {}".format(a))

# Nacin 2 (nad stringom se navodi % (a1, a2, ..., an))
# Argumenti posle % se unifikuju redom sa formatima navedenim u stringu.
print("a = %d" % a)

stepen = 10
b = 2
print("%.2f^%d = %.2f" % (b, stepen, b**stepen))
