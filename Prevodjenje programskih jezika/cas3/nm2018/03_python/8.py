#! /usr/bin/env python
# -*- coding: utf-8 -*-

import sys



args = sys.argv[1:]

suma = 0
for arg in args:
    suma += int(arg)
print("suma = %d" % suma)