#! /usr/bin/env python

import sys

def main():
    usr_input = ""
    print("Insert a, b or c: ")

    starting = 1
    ending = [3, 4]
    failure = 5
    transitioning = {
        (1, 'a') : 2,
        (1, 'c') : 2,
        (1, 'b') : 3,
        (2, 'a') : 2,
        (2, 'c') : 2,
        (2, 'b') : 3,
        (3, 'b') : 3,
        (3, 'a') : 5,
        (3, 'c') : 4,
        (4, 'a') : 5,
        (4, 'b') : 5,
        (4, 'c') : 4
    }

    while True:
        try:
            letter = input()
            if letter != 'a' and letter != 'b' and letter != 'c':
                raise ValueError("Neither a, b or c on input")
            usr_input += letter
            starting = transitioning[(starting, letter)]
            if starting == 5:
                print("Nope")
                sys.exit()
        except EOFError:
            print("Ctrl + D")
            break
        except ValueError as e:
            print(e)
            sys.exit()

    if starting in ending:
        print(usr_input + " -> Yep")
    else:
        print(usr_input + " -> Nope")


if __name__ == "__main__":
    main()