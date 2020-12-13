#! /bin/sh
# Uputstvo:
# ./compile DATOTEKA

if [[ "$#" -ne 1 ]]; then
    echo "usage: ./compile FILENAME"
    exit
fi

echo "Kompiliram $1"
g++ -Wall -Wextra -std=c++14 $1
