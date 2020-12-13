#! /usr/bin/env python
# -*- coding: utf-8 -*-
import os, sys, re


def input_data(fname=""):
    """
    Ucitava podatke i vraca ucitane podatke ka      o string.
    """ 
    try:
        with open(fname, "r") as f:
            return f.read()
    except IOError:
        sys.exit('Failed opening {}'.format(fname))

def parse_args(program_args):
    """
    Parsira argumente komandne linije i vraca mapu
    koja sadrzi indikatore o prosledjenim argumentima.
    """
    parsed_args = {
        'naziv': False,
        'repo': False,
        'verzija': False,
        'veb': False,
        'opis': False,
        'sve': False
    }

    if '-a' in program_args:
        parsed_args['sve'] = True
        return parsed_args, None
    
    if '-o' in program_args: parsed_args['opis'] = True
    if '-r' in program_args: parsed_args['repo'] = True
    if '-v' in program_args: parsed_args['verzija'] = True
    if '-w' in program_args: parsed_args['veb'] = True

    return parsed_args, program_args[-1]

def get_package_regex():
    """Vraca regularni izraz koji izvlaci jedan paket iz xml datoteke."""
    reg = re.compile(r'<paket\s*id="[0-9]+">.*?</paket>', re.DOTALL)
    return reg

def get_package_details(data):
    try:
        naziv = re.findall('<naziv>(.*?)</naziv>', data)[0]
        repo = re.findall('<repo>(.*?)</repo>', data)[0]
        veb = re.findall('<veb>((www\.)?([a-z-A-Z]+\.)+(org|com))</veb>', data)[0][0]
        opis = re.findall('<opis>(.*?)</opis>', data)[0]
        verzija = re.findall('<verzija>(\d+\.\d+\.\d+)</verzija>', data)[0]
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

def pretty_package_show(p):
    return '[{}] v{} {}\n{}\n{}'.format(p['naziv'], p['verzija'], p['repo'], p['veb'], p['opis'])

def main():
    if not (len(sys.argv) >= 2 and len(sys.argv) <= 6):
        sys.exit('usage:\n\tmatfpip.py [-v -o -r -w] name\n\tmatfpip.py -a')
    data = input_data("podaci.xml")

    args, package_name = parse_args(sys.argv)

    reg = get_package_regex();
    packages = []
    for paket in reg.finditer(data):
        paket_data = paket.group()
        package_details = get_package_details(paket_data)
        if package_details != None:
            # print('Adding {}'.format(package_details['naziv']))
            packages.append(package_details)

    # Proveravamo prosledjene argumente i postupamo u skladu sa njima.
    if args['sve']:
        # Sortiramo
        packages.sort(key=lambda x: x['naziv'])
        for pack in packages:
            print(pretty_package_show(pack))
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

if __name__ == "__main__":
    main()
