#! /usr/bin/env python
# -*- coding: utf-8 -*-
import os, sys, re

def get_package_details(data):
    try:
        naziv = re.findall('<naziv>(.*?)</naziv>', paket_data)[0]
        repo = re.findall('<repo>(.*?)</repo>', paket_data)[0]
        veb = re.findall('<veb>((www\.)?([a-z-A-Z]+\.)+(org|com))</veb>', paket_data)[0][0]
        opis = re.findall('<opis>(.*?)</opis>', paket_data)[0]
        verzija = re.findall('<verzija>(\d+\.\d+\.\d+)</verzija>', paket_data)[0]
    except IndexError:
        # IndexError ce biti ispaljen za slucaj da regularni izraz
        # ne pronadje potrebne informacije pa se pokusava indeksiranje
        # u vracenim rezultatima.
        return None

    return {
        'naziv': naziv,
        'repo': repo,
        'opis': opis,
        'veb': veb,
        'verzija': verzija
    }




if not (len(sys.argv) >= 2 and len(sys.argv) <= 6):
    sys.exit('usage:\n\tmatfpip.py [-v -o -r -w] name\n\tmatfpip.py -a')

try:
    with open("paketi.xml", "r") as f:
        data = f.read()
except IOError:
    sys.exit('Failed opening paketi.xml')


#"""Mapa koja sadrzi indikatore o prosledjenim argumentima."""
args = {
    'naziv': False,
    'repo': False,
    'verzija': False,
    'veb': False,
    'opis': False,
    'sve': False
}

package_name = None

if '-a' in sys.argv:
    args['sve'] = True

else: 
    if '-o' in sys.argv: 
        args['opis'] = True
    if '-r' in sys.argv: 
        args['repo'] = True
    if '-v' in sys.argv: 
        args['verzija'] = True
    if '-w' in sys.argv: 
        args['veb'] = True
    
    if sys.argv[-1][0] == '-':
        exit("Missing package name")
    else:
        package_name = sys.argv[-1]




""" Regularni izraz koji izvlaci jedan paket iz xml datoteke."""
reg = re.compile(r'<paket\s*id="[0-9]+">.*?</paket>', re.DOTALL)




packages = []

for paket in reg.finditer(data):
    paket_data = paket.group()
    package_details = get_package_details(paket_data)
    
    try:
        naziv = re.findall('<naziv>(.*?)</naziv>', paket_data)[0]
        repo = re.findall('<repo>(.*?)</repo>', paket_data)[0]
        veb = re.findall('<veb>((www\.)?([a-z-A-Z]+\.)+(org|com))</veb>', paket_data)[0][0]
        opis = re.findall('<opis>(.*?)</opis>', paket_data)[0]
        verzija = re.findall('<verzija>(\d+\.\d+\.\d+)</verzija>', paket_data)[0]
    except IndexError:
        # IndexError ce biti ispaljen za slucaj da regularni izraz
        # ne pronadje potrebne informacije pa se pokusava indeksiranje
        # u vracenim rezultatima.
        continue

    package_details =  {
        'naziv': naziv,
        'repo': repo,
        'opis': opis,
        'veb': veb,
        'verzija': verzija
    }
    
    # print('Adding {}'.format(package_details['naziv']))
    packages.append(package_details)

# Proveravamo prosledjene argumente i postupamo u skladu sa njima.
if args['sve']:
    # Sortiramo
    packages.sort(key=lambda x: x['naziv'])
    for pack in packages:
        print('[{}] v{} {}\n{}\n{}'.format(pack['naziv'], pack['verzija'], pack['repo'], pack['veb'], pack['opis']))
        print()
else:
    # Trazimo paket koji je uneo korisnik
    i = -1
    for k, p in enumerate(packages):
        if p['naziv'] == package_name:
            i = k
            break
    if i != -1:
        if args['opis']: print('Opis: {}'.format(packages[i]['opis']))
        if args['verzija']: print('Verzija: {}'.format(packages[i]['verzija']))
        if args['veb']: print('Opis: {}'.format(packages[i]['veb']))
        if args['repo']: print('Opis: {}'.format(packages[i]['repo']))
    else:
        print('Paket {} nije pronadjen.'.format(package_name))

