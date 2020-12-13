#! /usr/bin/env bash

egrep -o '^[A-Za-z_-]+\:' /etc/passwd \
| sort -r \
| sed -r 's/\://g' \
| egrep -n '.*' \
| sed -r 's/\:/. /g' \