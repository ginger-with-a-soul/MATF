#! /usr/bin/env python

def stepen_dvojke(x):
    return x*x

def main():

    x = int(input("Unesi x: "))

    if stepen_dvojke(x) > 16:
        print("Veci od 16")
    elif stepen_dvojke(x) < 16:
        print("Manji od 16")
    else:
        print("Tacno 16!")
    
if __name__ == "__main__":
    main()