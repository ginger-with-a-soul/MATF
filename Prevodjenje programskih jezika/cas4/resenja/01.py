#! /usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import re


def create_regex_stn():
    """
    Funkcija vraca regularni izraz koji prepoznaje UNITEX entitete.
    grupa 1: originalni sadrzaj teksta
    grupa 2: prepoznati entitet
    """
    return re.compile(r'{(.*?)[.]NE\+([a-zA-Z]+):\d+[a-z]+}', re.DOTALL)

def main():
    if len(sys.argv) != 2:
        sys.exit('usage: 01.py input_file')

    with open(sys.argv[1], 'r') as f:
        print('Reading input data')
        data = f.read()
        print('Done!')

    print('Prepoznati tokeni:')
    stn_regex = create_regex_stn()
    for matched_item in stn_regex.finditer(data):
        print(matched_item)

    # Vrsimo zamenu u tekstu
    new_data = re.sub(stn_regex, r'<\2>\1<\2>', data)

    output_file_name = sys.argv[1].split('.')[-1] + '.xml'
    with open(output_file_name, 'w') as f:
        f.write('<xml>\n')
        f.write(new_data)
        f.write('</xml>')
        print('Wrote results at ' + output_file_name)


if __name__ == "__main__":
    main()
