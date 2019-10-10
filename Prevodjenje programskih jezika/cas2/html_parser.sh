#! /usr/bin/env bash

egrep -o -h '<\s*td\s*>[A-Za-z]+\s+[A-Za-z]+<\s*\/td\s*>\s*<\s*td\s*>[0-9]{3}\/[0-9]{4}<\s*\/td\s*>' nastava*.html \
| sed -r 's/<td>//g' \
| sed -r 's/<\/td>/ /g' \
| sed -r 's/([A-Za-z]+) ([A-Za-z]+)/\2 \1/g' \
| sed -r 's/([0-9]{3})\/[0-9]{2}([0-9]{2})/mi\2\1/g' \
| sort \
| egrep -n '.*' \
| sed -r 's/\:/. /g' \