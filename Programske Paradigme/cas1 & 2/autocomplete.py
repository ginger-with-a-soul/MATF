try:
    with open('reci.txt', 'r') as file:
        data = file.read()
except IOError as err:
    print(err)

while True:
    getString = str(input("?: "))
    if getString == '!':
        break

    for word in data.split():
        if word.find(getString, 0, len(getString)) != -1:
            print(word)
