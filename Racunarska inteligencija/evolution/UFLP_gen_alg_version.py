import random

class Individual:

	def __init__(self, numRes, numUsr, cost, fixedCost):
		self.cost = cost
		self.fixedCost = fixedCost
		self.code = []
		for _ in range(numRes):
			self.code.append(random.uniform(0, 1) < 0.25)
		self.correctNonFeasible()
		self.fitness = 0

	def __lt__(self, other):
		return self.fitness < other.fitness
	
	def correctNonFeasible(self):
		if any(self.code):
			self.fitness =  self.fitnessFunction(cost, fixedCost)
			return
		index = random.randrange(len(self.code))
		self.code[index] = True
		self.fitness =  self.fitnessFunction(cost, fixedCost)


	def fitnessFunction(self, cost, fixedCost):
		value = 0.0
		numUsr = len(cost)
		numRes = len(fixedCost)
		used = [False] * numRes

		for i in range(numUsr):
			mini = float('inf')
			j_used = -1
			for j in range(numRes):
				if self.code[j] and mini > cost[i][j]:
					mini = cost[i][j]
					j_used = j
			
			value += mini
			used[j_used] = True

		for i in range(numRes):
			if used[i]:
				value += fixedCost[i]
		
		return value

def read_input(filename):
	f = open(filename, "r")
	numUsr, numRes = [int(i) for i in f.readline().split()]
	cost = [[int(i) for i in f.readline().split()] for _ in range(numUsr)]
	fixedCost = [int(i) for i in f.readline().split()]

	return numUsr, numRes, cost, fixedCost

def selection(population, tournament_size):
	index = -1
	mini = float('inf')
	for _ in range(tournament_size):
		k = random.randrange(len(population))
		if mini > population[k].fitness:
			mini = population[k].fitness
			index = k
	
	return population[index]

def crossover(p1, p2, c1, c2):
	index = random.randrange(len(p1.code))
	c1.code[:index] = p1.code[:index]
	c1.code[index:] = p2.code[index:]
	c2.code[:index] = p2.code[:index]
	c2.code[index:] = p1.code[index:]

	c1.correctNonFeasible()
	c2.correctNonFeasible()


def mutation(population, mutation_size, mutation_rate, numRes, population_size):
	for _ in range(mutation_size):
		ind_index = random.randrange(population_size)
		gen_index = random.randrange(numRes)
		if random.uniform(0, 1) <= mutation_rate:
			population[ind_index].code[gen_index] = not population[ind_index].code[gen_index]
			population[ind_index].fitness = population[ind_index].correctNonFeasible()


def gen_alg(numUsr, numRes, cost, fixedCost, population_size, max_iterations, mutation_size, mutation_rate, tournament_size, elite_size):

	population = []
	for _ in range(population_size):
		population.append(Individual(numRes, numUsr, cost, fixedCost))
	
	for iteration in range(max_iterations):
		population.sort()

		new_population = []
		for k in range(elite_size):
			new_population.append(population[k])
		
		for i in range(elite_size, population_size, 2):
			p1 = selection(population, tournament_size)
			p2 = selection(population, tournament_size)
			c1 = Individual(numRes, numUsr, cost, fixedCost)
			c2 = Individual(numRes, numUsr, cost, fixedCost)

			crossover(p1, p2, c1, c2)

			new_population.append(c1)
			new_population.append(c2)
		
		mutation(population, mutation_size, mutation_rate, numRes, population_size)

		population = new_population
	
	return min(population)


if __name__ == "__main__":

	numUsr, numRes, cost, fixedCost = read_input("input.txt")

	result = gen_alg(numUsr, numRes, cost, fixedCost, 300, 40, 30, 0.04, 30, 30)

	print(result.fitness)