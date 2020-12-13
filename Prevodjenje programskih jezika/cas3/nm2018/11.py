#! /usr/bin/env python

#formirati dva skupa, prolaz, unija, presek, razlika, podskup
def main():

    s1 = {1, 2, 3}
    s2 = {1, 2, 3, 4, 5}

    print("s1 unija s2: %s \ns1 presek s2: %s \ns1 razlika s2: %s" % (str(s1.union(s2)), str(s1.intersection(s2)), str(s1.difference(s2))))

    if s1.issubset(s2):
        print("s1 jeste podskup s2")
    else:
        print("s1 nije podskup s2")

if __name__ == "__main__":
    main()