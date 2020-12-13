import json
import datetime as dt

try:
    with open('ispiti.json', 'r') as file:
        data = json.load(file)
except IOError as err:
    print(err)

for entry in data:
    d, m, y, x = entry['datum'].split('.')
    date = dt.date(int(y), int(m), int(d))
    if date > dt.datetime.now().date():
        print(f"Naziv: {entry['ime']}. Status: ostalo je jos {date.day - dt.datetime.today().day} dana")
    else:
        print(f"Naziv: {entry['ime']}. Status: prosao")
