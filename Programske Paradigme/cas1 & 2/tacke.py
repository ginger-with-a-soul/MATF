import json

try:
    with open('temena.json', 'r') as file:
        x = json.load(file)
except IOError as err:
    print(err)

for i in x:
    print(i['teme'])

newX = sorted(x, key=lambda y: y[' koordinate '][0] ** 2 + y[' koordinate '][1] ** 2)

for i in newX:
    print(i['teme'])