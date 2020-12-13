# read text file char by char
import json
import requests

with open('1.txt', 'r') as file:
    for line in file:
        for char in line:
            print(char)


try:
    with open('2.txt', 'r') as file:
        for line in file:
            print(line)
except IOError as err:
    print(err)

try:
    with open('1.txt', 'a+') as file:
        file.write("\nsomething new in file\n")
        file.flush()
        file.seek(0, 0)
        print(file.readlines())
except IOError as error:
    print(error)

name = input("Name? ")
surname = input("Surname? ")
age = input("Age? ")

hero = {
    "Name": name,
    "Surname": surname,
    "Age": age
}

print(json.dumps(hero))

try:
    with open('file.json', 'w') as file:
        json.dump(hero, file)
except IOError as err:
    print(err)

try:
    with open('file.json', 'r') as file:
        x = json.load(file)
except IOError as err:
    print(err)

for v in x:
    print(x[v])


url = 'https://quotes.rest/qod'

response = requests.get(url)

if response.ok:
    json = response.json()
    quote = json['contents']['quotes'][0]['quote']
    print(quote)
else:
    print('Error getting the response')