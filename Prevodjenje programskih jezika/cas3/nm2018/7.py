#! /usr/bin/env python

#spojiti dva string, naci string u stringu, stampati deo stringa, od liste napraviti string

def main():

    s1 = "Da li se neko zoveDimitrije"
    s2 = "i preziva Stankov"
    s3 = "?"

    cs = s1 + " " + s2 + "" + s3
    print("Ceo string: %s" % cs)
    
    
    i = cs.find("preziva")

    if i != -1:
        print("Postoji needle: %i" % i)
        print("Needle je: %s" % (cs[i:i+len("preziva")+1]))
    else:
        print("Ne postoji needle!")

    lista = ["Neki", "string", "koji", "veze", "nema", 2]
    lista2 = []
    for x in range(0, len(lista)):
        if(isinstance(lista[x], str)):
            lista2.append(lista[x])

    ncs = " ".join(lista2)

    print("String od liste: %s" % ncs)

if __name__ == "__main__":
    main()