#! /usr/bin/env python

#sabrati n-torke, pomnoziti ih skalarom, ispisati ih od nekog do nekog dela
def main():

    n1 = (1, 2)
    n2 = (10, 20)

    def inkrementiraj(x, y):
        x += 1
        y += 1
        return (x, y)
    
    n3 = n1 + n2
    print(n3)
    print("n3 * 3 == %s" % str(n3*3))
    n4 = (1, 2, 3, 10, 12, 13, 24, 15, 11, 221)

    n_4 = n4[2:7]
    print("n_4: %s" % str(n_4))
    print("inkrementiran n1: %i %i" % (inkrementiraj(n1[0], n1[1])))

if __name__ == "__main__":
    main()