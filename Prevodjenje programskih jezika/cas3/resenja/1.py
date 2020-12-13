#!/usr/bin/python3

# prva linija u programu treba da bude putanja do interpretera
# podrazumevano, na sistemu se koristi python2 i putanja do njega je 
#
# #!/usr/bin/python
#
# s obzirom da nam na kursu treba python3, putanja mora da se navede
# explicitno sa
#
# #!/usr/bin/python3
#

# Ukljucujemo zaglavlje
import sys

# stampanje na standardni izlaz se postize funkcijom print
# BITNO:
# python3 zahteva da argumenti budu uokvireni zagradama, u surprotnom 
# prijavljuje sintaksnu gresku
# python2 nema takav zahtev i print bez zagrada je validan
print("Hello world!\n")

# python je dinamicki tipiziran i ne postoji potreba za eksplicitnim 
# definisanjem tipova kao u C
# Medjutim, ako vam treba neki operator koji je definisan samo na jednoj klasi tipova,
# neophodno je eksplicitno kastovanje
x = 2
y = 3

# print funkcija podrzava promenljivi broj argumenata. Ako se stampa veci
# broj promenljivih dovoljno je odvojiti ih zarezima
print (x, y)

print (x + y)	# sabiranje
print (x/y)		# realno deljenje
print (x//y)	# kolicnik pri deljenju
print (x%y)		# ostatak pri deljenju

print (x**y)	# stepenovanje

z = 3+2j		# kompleksni broj. BITNO: kompleksna jedinica se obelezava sa j, a ne sa i

print (z)
print (z.real, z.imag) 	# realni i imaginarni deo kompleksnog broja

print (z + complex(2 + 3j))	# sabiranje kompleksnih brojeva
print (abs(-5))		# sve osnovne matematicke funkcije su ugradjene u python.
					#sqrt,sin,cos,log,exp....


