#!/usr/bin/python3

import sys

stanje = 'P'
zavrsno ='P'

prelaz ={('P','0'):'N', ('P','1'):'P', ('N', '0'): 'P', ('N','1'):'N' }

while True:
        try:
                c = input('Unesite 0 ili 1: ')
                if (c != '0' and c !='1' ):
                        raise ValueError('Nije uneta ni 0 ni 1')
        except EOFError:
                break
        except ValueError as e:
                print (e)
                sys.exit()
 
        stanje = prelaz[(stanje,c)]
        print ("\t" + stanje)
 

if stanje == zavrsno :
        print ('Rec ima paran broj nula')
else:
        print ('Rec nije prihvacena automatom')