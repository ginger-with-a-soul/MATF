import bruteforce_iterative as bf
from random import choices
import ui_code

if __name__ == "__main__":

	#initializes the UI part of the app defined in ui_code.py
	app = ui_code.UiApp()
	app.run()

	k = app.get_size_input() #variation size
	n = int(input()) #number of variation symbols 
					 #combinatorial explosion: n^k different variations
	print(k)

	available_symbols = [x + 1 for x in range(n)] #returns a list of available symbols for
												  #variation to use based on n starting from
												  #1 and including n

	problem = choices(available_symbols, k=k) #initializes a problem that we want to solve using
											  #different techniques
	

	bf.generate_all(k, n)
