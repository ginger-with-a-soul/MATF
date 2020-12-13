#! /usr/bin/env bash

egrep '<td>[1-9][0-9]*<\/td><td>[A-Z]+\s[A-Z]+<\/td><td>19(8[6-9]|9[0-2])<\/td><td>(SLO|SRB)<\/td><td>.*?<td>.*?<td>.*?<td>.*?<td>1:[0-5][0-9]:[0-5][0-9]<\/td>' Ljubljana_muskarci.html Ljubljana_zene.html -o -h -n\
| sort -t '>' -k 2,2 -n \
| sed -r 's/<td>[1-9][0-9]*<\/td><td>([A-Z]+\s[A-Z]+)<\/td><td>(19(8[6-9]|9[0-2]))<\/td><td>((SLO|SRB))<\/td><td>.*?<td>.*?<td>.*?<td>.*?<td>(1:[0-5][0-9]:[0-5][0-9])<\/td>/\1 \6 \2 \4/g'
