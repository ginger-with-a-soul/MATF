#! /usr/bin/env python

def main():

	lista = [1, 3, "string", "nesto", [1, 2, 3]]

	for x in lista:
		print(x)

	i = 4

	print("Cetvrti element liste je: %s" % (lista[i]))

	lista2 = [10, 22, "opet", "nesto"]

	lista.extend(lista2)
	print(lista)

	print(lista.pop())

	k = (len(lista) // 2)
	print("Srednisnji element je: %s" % (lista[k-1]))

	lista.append("kurcina")

	print(lista.pop())

	lista.insert(0, 777)

	print(lista[0])

	print(lista.count([1, 2, 3]))
	print(lista.sort())

	lista.extend(lista2)


if __name__ == '__main__':
	main()