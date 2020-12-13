#! /usr/bin/env python

import sys

def main():

    usr_input = ""

    print("Input 1 or 0: ")

    state = 1
    ending = [4, 5]
    transitioning = {
        (1, 0) : 2,
        (1, 1) : 3,
        (2, 0) : 5,
        (2, 1) : 3,
        (3, 0) : 2,
        (3, 1) : 4,
        (4, 0) : 2,
        (4, 1) : 4,
        (5, 0) : 5,
        (5, 1) : 3
    }

    while True:
        try:
            c = input()
            usr_input += c
            if c.isdigit():
                c = int(c)
            if c != 0 and c != 1:
                raise ValueError("Neither 0 or 1")
        except EOFError:
            break
        except ValueError as e:
            print(e)
            sys.exit()

        state = transitioning[(state, c)]
        print("Current state: ", state)

    print("User input: ", usr_input)
    if state in ending:
        print("It does end with 00 or 11")
    else:
        print("It does not end with 00 or 11")

if __name__ == "__main__":
    main()