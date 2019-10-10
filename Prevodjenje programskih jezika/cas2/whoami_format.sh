#! /usr/bin/env bash
whoami \
| sed -r 's/(.*)/OS\: GNU\/Linux user\: [\1]/' \