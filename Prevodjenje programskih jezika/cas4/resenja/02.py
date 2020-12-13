#! /usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import re


"""
Napisati python-skript koji štampa na standardni izraz:
- autora (−a)
- cenu (−c),
- izdavača (−i)
- godinu izdanja (−g)
knjige koja se navodi kao argument komande linije,

u zavisnosti od prisutne opcije komandne linije (u slučaju da nema opcija, ispisati sve
podatke o traženoj knjizi).

Primeri pozivanja:
python 02.py -a 'Yacc'
autor: Filip Maric

python 02.py -a -g 'Yacc'
autor: Filip Maric
godina_izdanja: 2004
"""

separator = '-------------------------------------------------------'

def parse_args():
    """
    Vraca mapu parsiranih argumenata sa kljucevima:
    - autor
    - cena
    - izdavac
    - godina_izdanja
    """
    options = dict(zip(['autor', 'cena', 'izdavac', 'godina_izdanja'], [False] * 4))
    key_map = {'-c': 'cena', '-a': 'autor', '-i': 'izdavac', '-g': 'godina_izdanja'}

    n_args = len(sys.argv) - 1 - 1  # -1 zbog imena datoteke, i -1 zbog imena prosledjene knjige
    print('Broj prosledjenih opcija: {}'.format(n_args))

    if n_args == 0:
        options = dict(zip(['autor', 'cena', 'izdavac', 'godina_izdanja'], [True] * 4))
    else:
        for arg_elem in sys.argv[1:n_args+1]:
            options[key_map[arg_elem]] = True

    book_name = sys.argv[-1]

    return options, book_name

def create_xml_tag_regex(tag_name):
    return re.compile(r'<{0}( valuta="([a-zA-Z]+)")?>\s*(.*?)\s*</{0}>'.format(tag_name), re.DOTALL)

def create_book_regex():
    """
    Vraca xml sadrzaj koji sadrzi informacije o knjizi ciji je naslov jednak 'book_name'.
    """
    # return re.compile(r'<knjiga\s*rbr="\d+"\s*>.*?<\s*naslov\s*>\s*{}\s*</naslov>.*?</knjiga>'.format(book_name), re.DOTALL)
    return re.compile(r'<knjiga\s*rbr="\d+"\s*>.*?</knjiga>', re.DOTALL)

def get_book_data(book_name, data):
    book_regex = create_book_regex()

    # Iteriramo kroz dostupne knjige i trazimo onu koja ima naziv 'book_name'.
    print(book_name)
    for book_item in book_regex.finditer(data):
        print('item: ', book_item.group(0))
        # Pravimo pomocni regularni izraz koji trazi tag za naziv
        if re.search('<naslov>\s*{}\s*</naslov>'.format(book_name), book_item.group(0), re.DOTALL):
            # Vracamo xml reprezentacije trazene knjige.
            print('Found it!')
            return book_item.group(0)

    # Trazena knjiga nije pronadjena.
    return None

def main():
    options, book_name = parse_args()

    # Citamo podatke
    try:
        with open('knjige.xml', 'r') as f:
            data = f.read()
    except IOError as e:
        sys.exit("Neuspelo citanje datoteke\n{}".format(e))

    print("Prosledjene opcije: {}".format(options))
    print("Ime trazene knjige: {}".format(book_name))

    # Trazimo knjigu koju je prosledio korisnik
    book_data = get_book_data(book_name, data)
    print('\nPronadjeni sadrzaj za trazenu knjigu:')
    print(separator)
    print(book_data)
    print(separator)

    # Prolazi se kroz opcije koje je postavio korisnik
    # i prikazuju se trazeni podaci
    print('\n\n' + separator)
    for opt, toggled in options.items():
        if toggled and opt == 'cena':
            xml_regex = create_xml_tag_regex(opt)
            book_item_value = xml_regex.search(book_data)
            print(opt + ': ' + book_item_value.group(3) + book_item_value.group(2)) 
        elif toggled:
            xml_regex = create_xml_tag_regex(opt)
            book_item_value = xml_regex.search(book_data)
            print(opt + ': ' + book_item_value.group(3)) 
    print(separator)


if __name__ == "__main__":
    main()
