#! /usr/bin/env bash

egrep '^[a-zA-Z0-9]+:' passwd.txt -o -n \
| sed -r 's/:$//' \