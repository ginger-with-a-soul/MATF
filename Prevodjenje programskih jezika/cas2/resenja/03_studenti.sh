#! /usr/bin/env bash
# Radi dobijanja robusnijeg regularnog izraza neophodno bi bilo dodati \s* na mesta
# poput okolina td html elementa -> <\s*td\s*>...
# Taj korak u ovom resenju je izostavljen radi citljivosti.
# zastavica -o -> alat prikazuje samo sadrzaj koji je regex prihvatio, a ne liniju u kojoj
#                   se sadrzaj nalazi (sto je podrazumevano ponasanje).
egrep '<td>[a-zA-Z]+\s*[a-zA-Z]+</td><td>[0-9]{1,3}/[0-9]{4}</td>' nastava*.html -h -o \
| sed -r 's/<td>//g' \
| sed -r 's/<\/td>/ /g' \
| sed -r 's/([a-zA-Z]+) ([a-zA-Z]+) /\2 \1, /' \
| sed -r 's/([0-9]+)\/[0-9]{2}([0-9]{2})/mi\2\1/' \
| sort \
| egrep '.*' -n \
| sed -r 's/:/. /'

# ------------------------------------------------------------------------------------------------
# Objasnjenje
# ------------------------------------------------------------------------------------------------
# Izvlacimo td elemente.
    # egrep '<td>[a-zA-Z]+\s*[a-zA-Z]+</td><td>[0-9]{1,3}/[0-9]{4}</td>' nastava*.html -h -o \
# Skidamo tagove <td> i </td> pri cemu koristimo zastavicu g da zamenimo SVA
# pojavljivanja regex-a u liniji umesto PRVOG (sto je podrazumevano).
    # | sed -r 's/<td>//g' \
    # | sed -r 's/<\/td>/ /g' \
# Menjamo redosled u podacima za ime i prezime.
    # | sed -r 's/([a-zA-Z]+) ([a-zA-Z]+) /\2 \1, /' \
# Indeks iz formata XXX/YYYY menjamo u format miYYXXX
    # | sed -r 's/([0-9]+)\/[0-9]{2}([0-9]{2})/mi\2\1/' \
# Sortiramo po imenima studente
    # | sort \
# BITNO: Kako dodati redne brojeve linijama?
# Moze se koristiti zastavica -n za egrep
    # | egrep '.*' -n \
# Jos malo sredujemo prikaz, odnosno skidamo : koju
# je prethodna linija dodala.
    # | sed -r 's/:/. /'
# ------------------------------------------------------------------------------------------------

