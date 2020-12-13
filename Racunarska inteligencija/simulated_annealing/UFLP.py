import random

def getInput(filepath):
	try:
		info = open(filepath, "r")
	except ValueError:
		print(ValueError)

	clientNum, resourceNum = [int(i) for i in info.readline().split()]
	linkCosts = [[int(i) for i in info.readline().split()] for j in range(clientNum)]
	resourceCosts = [int(i) for i in info.readline().split()]
	
	return clientNum, resourceNum, linkCosts, resourceCosts

def isFeasible(resourceNum, solution):
	for i in range(resourceNum):
		if solution[i]:
			return True
	return False

def initializeSolution(resourceNum, probability):
	solution = []
	for i in range(resourceNum):
		solution.append(random.random() < probability)
	
	if not isFeasible(resourceNum, solution):
		solution[random.randrange(resourceNum)] = True
	return solution

def solutionValue(clientNum, resourceNum, linkCosts, resourceCosts, solution):
	usedResources = [False] * resourceNum
	value = 0.0

	for i in range(clientNum):
		minCost = float('inf')
		used = -1
		for j in range(resourceNum):
			if solution[j] and linkCosts[i][j] < minCost:
				minCost = linkCosts[i][j]
				used = j
		usedResources[used] = True
		value += minCost

	for i in range(resourceNum):
		if usedResources[i]:
			value += resourceCosts[i]
	
	solution = usedResources
	return value

def invert(solution):
	n = len(solution)
	x = random.randrange(n)
	solution[x] = not solution[x]
	if not isFeasible(n, solution):
		return -1
	else:
		return x

def revertSolution(solution, i):
	solution[i] = not solution[i]

def simulatedAnnealing(clientNum, resourceNum, linkCosts, resourceCosts, solution, iters):
	bestValue = solutionValue(clientNum, resourceNum, linkCosts, resourceCosts, solution)
	currValue = bestValue

	i = 1.0
	for i in range(iters):
		j = invert(solution)
		if j == -1:
			continue

		newValue = solutionValue(clientNum, resourceNum, linkCosts, resourceCosts, solution)
		if newValue < currValue:
			currValue = newValue
		else:
			p = 1.0 / i ** 0.5
			q = random.uniform(0, 1)
			if p > q:
				currValue = newValue
			else:
				revertSolution(solution, j)
		
		if bestValue > currValue:
			bestValue = currValue

	return bestValue


def main():

	clientNum, resourceNum, linkCosts, resourceCosts = getInput("input.txt")
	solution = initializeSolution(resourceNum, 0.25)
	
	value = simulatedAnnealing(clientNum, resourceNum, linkCosts, resourceCosts, solution, 10000)

	print(f"Best value is: {value}")
	

if __name__ == "__main__":
	main()