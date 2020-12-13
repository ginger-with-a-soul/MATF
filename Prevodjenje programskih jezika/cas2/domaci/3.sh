#! /usr/bin/env bash

egrep '[-a-z]+:x:[0-9]{1,4}' group.txt -o \
| sed -r 's/([-a-z]+):(x):([0-9]{1,4})/<tr><td>\1<\/td><td>\2<\/td><td>\3<\/td>/g' \
| sed -r '1s/^/<h3>Grupe<h3><table border="1">/' \
| sed -r '$s/$/\n<\/table>/' > grupe.html