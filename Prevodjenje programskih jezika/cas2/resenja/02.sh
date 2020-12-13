#! /usr/bin/env bash

# Ispisuje sve linije koje sadrze rec HP
# -> Preporuka je regularni izraz koji se prosledjuje alatu pisati pod navodnicima.
# egrep 'HP' laptops.txt

# Mi zelimo da saznamo tacno broj linije koja zadovoljava
# da sadrzi rec HP.
# U tu svrhu, u man stranama za alat egrep mozemo da
# potrazimo zastavicu koja to mogucava.
# $ man egrep
# -> Zastavica -n
printf 'Laptop racunari proizvodjaca HP:\n'
egrep -n 'HP' laptops.txt

# Koliko linija zadovoljava nas regularni izraz?
# Prvi nacin:
# -> Izlaz prve naredbe prosledjujemo komandi wc
#    koja prebrojava linije (zastavica -l)
printf '\nBroj linija koje zadovoljavaju regex: '
egrep -n 'HP' laptops.txt | wc -l
# Drugi nacin:
# -> Alat (e)grep ima zastavicu koja prebrojava rezultate
printf 'Broj linija koje zadovoljavaju regex: '
egrep -c 'HP' laptops.txt

