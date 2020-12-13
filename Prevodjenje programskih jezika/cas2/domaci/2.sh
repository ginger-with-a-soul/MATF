#! /usr/bin/env bash

whoami > kosamja.txt \
| egrep '[a-zA-Z0-9]+' kosamja.txt \
| sed -r 's/([a-zA-Z0-9]+)/OS GNU\/Linux user: [\1]/g'