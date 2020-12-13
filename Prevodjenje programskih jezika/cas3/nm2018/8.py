#! /usr/bin/env python

import sys

def main():

    if len(sys.argv) == 1:
        print(0)
        sys.exit(0)
    
    args = sys.argv[1:]

    sum = 0

    for arg in args:
        sum += int(arg)

    print(sum)

if __name__ == "__main__":
    main()