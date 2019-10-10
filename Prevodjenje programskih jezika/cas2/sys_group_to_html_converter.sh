#! /usr/bin/env bash

printf '<h3>Group<h3>\n<table border = "1">\n' >> group.html
egrep -o '[A-Za-z_-]+\:x\:[0-9]+' /etc/group \
| sed -r 's/([A-Za-z_-]+)\:(x)\:([0-9]+)/<tr><td>\1<\/td><td>\2<\/td><td>\3<\/td><\/tr>/g' >> group.html
printf '</table>\n' >> group.html