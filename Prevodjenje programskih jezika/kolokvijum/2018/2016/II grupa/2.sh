#! /usr/bin/env bash

egrep '[0-9.]{8}	mi1[0-9]{4}	[a-zA-Z]+\s[a-zA-Z]+	(1[0-4]|[0-9]).[0-9]{2}	[1-9]?[0-9].[0-9]{2}	[1-9]?[0-9].[0-9]{2}	[a-zA-Z0-9]+$' *.txt -h -o \
| sort -k 5,5 -d \
| sed -r 's/[0-9.]{8}	(mi1[0-9]{4})	([a-zA-Z]+)\s([a-zA-Z]+)	(1[0-4]|[0-9]).[0-9]{2}	([1-9]?[0-9].[0-9]{2})	([1-9]?[0-9].[0-9]{2})	([a-zA-Z0-9]+$)/\2	\3	\1	\7	\6	\5/g'
