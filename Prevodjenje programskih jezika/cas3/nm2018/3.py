#! /usr/bin/env python
def main():
	n = int(input("Unesite broj: "))

	for i in range(0, n):
		if i % 2 == 0:
			print(i)

	while n:
		print(n % 10)
		n //= 10
if __name__ == '__main__':
	main()