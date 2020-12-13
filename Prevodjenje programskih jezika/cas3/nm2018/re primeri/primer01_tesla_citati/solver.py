import sys

def is_not_empty(s):
    s = s.strip()
    return s != "" and s != "\n"

def main():
    if len(sys.argv) != 2:
        sys.exit('Molimo unesite putanju do datoteke...')

    path_input = sys.argv[1]

    try:
        with open(path_input, 'r', encoding='utf-16') as f:
            print('Ucitavaju se podaci...')
            data = f.read()
            quotes = data.split(";;")
            quotes = list(filter(is_not_empty, quotes))
            print('Ucitani su podaci i eliminisani losi podaci.')

    # Ukoliko zelimo da hvatamo izuzetak:
    except IOError as e:
        print(e.message)
        sys.exit('Neuspelo otvaranje datoteke...')

    path_output = 'quotes.xml'
    print('Otvara se datoteka za citanje...')
    try:
        with open(path_output, 'w') as f:
            print('Vrsi se upis u datoteku...')
            f.write("<tesla-quotes>\n")
            for quote in quotes:
                f.write("\t<item>{}</item>\n".format(quote))
                # f.write("<item>%s</item>\n" % quote)
            f.write("</tesla-quotes>")
    except IOError:
        sys.exit('Neuspelo otvaranje datoteke za pisanje...')

    print('Generisana je datoteka {}'.format(path_output))

if __name__ == "__main__":
    main()
