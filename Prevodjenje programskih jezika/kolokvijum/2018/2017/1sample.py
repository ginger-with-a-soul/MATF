#! /usr/bin/python3
import sys
import re

def f1(file_name):
    try:
        with open(file_name, 'r') as f:
            sadrzaj = f.read()

    except IOError as e:
        print(e.message)
        sys.exit("Budi se HAMA")

    pattern = r"([a-zA-Z ]+),\s([a-zA-Z ]+),\s([0-9]+),\s([0-9]+),\s([0-9]+)-([0-9]+)?,\s([a-zA-Z, ]+)"

    fudbaler = []

    re_compiled = re.compile(pattern)
    for x in re_compiled.finditer(sadrzaj):
        n = float(x.group(3))
        n = n / float(x.group(4))
        ime = x.group(1)
        fudbaler.append({
            'ime' : x.group(1),
            'koeficijent' : n
        })

    def poredjenje(fud):
        return fud['koeficijent']

    fudbaler.sort(key=poredjenje, reverse=True)

    for fud in fudbaler:
        print(fud['ime'] + " " + "{:.2f}".format(fud['koeficijent']))

def f2(file_name, klub):
    try:
        with open(file_name, 'r') as f:
            sadrzaj = f.read()

    except IOError as e:
        print(e.message)
        sys.exit("Budi se HAMA")

    pattern = r"([a-zA-Z ]+),\s([a-zA-Z ]+),\s([0-9]+),\s([0-9]+),\s([0-9]+)-([0-9]+)?,\s([a-zA-Z, ]+)"

    fudbaler = []

    s = ""
    godina = 0
    re_compiled = re.compile(pattern)
    for x in re_compiled.finditer(sadrzaj):
        s = str(x.group(7))
        if x.group(6) == None:
            godina = 2018
        else:
            godina = int(x.group(6))
        if klub in s:
            print(x.group(1) + " " + x.group(5) + " " + "{:d}".format(godina - int(x.group(5))))

def main():
    if len(sys.argv) < 3:
        print("Br argumenata vrljav")
        sys.exit()

    num = len(sys.argv)

    file_name = sys.argv[1]
    check = ''
    check = file_name[-4] + file_name[-3] + file_name[-2] + file_name[-1]

    if check != '.csv':
        sys.exit("Duvaj karu")

    klub = ''

    for rec in sys.argv[3:num]:
        klub += rec
        klub += " "

    klub = klub[:-1]

    if sys.argv[2] == '-g':
        f1(file_name)
    elif sys.argv[2] == '-t':
        f2(file_name, klub)
    else:
        print("Zajebo si se")

if __name__ == "__main__":
    main()
