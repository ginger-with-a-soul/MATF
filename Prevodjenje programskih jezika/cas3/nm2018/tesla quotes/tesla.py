#! /usr/bin/env python

import sys
import io

def string_strip(quotes):
    quotes = quotes.strip()
    return quotes != "" and quotes != "\n"

def main():

    if len(sys.argv) != 3:
        sys.exit("Los unos argumenata!")

    open_path = sys.argv[1]
    write_path = sys.argv[2]

    try:
        with open(open_path, 'r') as f:
            data = f.read()
            quotes = data.split(";;")
            quotes = list(filter(string_strip, quotes))
    except IOError as e:
        sys.exit(e.message)

    try:
        with open(write_path, "w") as f:
            f.write("<tesla-quotes>")
            for quote in quotes:
                f.write("<item>%s</item>" % quotes)
            f.write("</tesla-quotes>")
    except IOError as e:
        sys.exit(e.message)


if __name__ == "__main__":
    main()