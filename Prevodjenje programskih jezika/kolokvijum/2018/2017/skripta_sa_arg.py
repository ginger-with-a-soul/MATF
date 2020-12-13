#! /usr/bin/env python

import sys
import re

def main():

    if len(sys.argv) < 3 || len(sys.argv) > 4:
        sys.exit("Bad argument count")

    input_path = argv[1]

    if not input_path.endswith(".csv"):
        sys.exit("Input doesn't end with \".csv\"")

    try:
        with open(input_path, "r") as f:
            data = f.read();
    except IOError as e:
        sys.exit(e.message)




if __name__ == "__main__":
    main()