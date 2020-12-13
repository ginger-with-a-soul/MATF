#! /usr/bin/env bash

egrep '([a-zA-Z ]+),\s([a-zA-Z ]+),\s[0-9]+,\s([0-9]{3}),\s+([0-9]+)-([0-9]+),\s([a-zA-Z0-9, ]+)' igraci.csv -h \
| sed -r 's/([a-zA-Z ]+),\s([a-zA-Z ]+),\s[0-9]+,\s([0-9]{3}),\s+([0-9]+)-([0-9]+),\s([a-zA-Z0-9, ]+)/\1 (\2) [\4-\5]: \6/g' \
| sed -r 's/,/->/g'