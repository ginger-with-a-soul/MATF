'''
Iterative bruteforce algorithm for generating all 
variations that are k long using n different symbols
'''
def generate_all(k:int, n:int):

	'''
	Generates all variations starting from all 1s. Variations are
	changed from back to front
	'''

	current_variation = k * [1]
	

	exists_next_variation = True
	while(exists_next_variation):
		print(current_variation)

		index = k - 1
		while(index >= 0 and current_variation[index] == n):
			current_variation[index] = 1
			index -= 1

		if index < 0:
			exists_next_variation = False
		else:
			current_variation[index] += 1