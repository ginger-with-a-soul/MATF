import constraint

problem = constraint.Problem()

domainZ = [pow(i, 3) for i in range (1, 11)]
print(domainZ)

problem.addVariable('X', range(1, 11))
problem.addVariable('Y', range(1, 52, 2))
problem.addVariable('Z', range(10, 101, 10))
problem.addVariable('W', domainZ)

problem.addConstraint(lambda X, W: X >= 2 * W, ['X', 'W'])
problem.addConstraint(lambda Y, Z: Z >= 3 + Y, ['Z', 'Y'])
problem.addConstraint(lambda X, W, Z, Y: 100 >= X - 11 * W + Y + 11 * Z, ['X', 'W', 'Z', 'Y'])

r = problem.getSolutions()

print('−−−−−−−−−−−−−−−−−−−−−−−−')
for s in r:
	print(f'X = {s["X"]}	Y = {s["Y"]}	Z = {s["Z"]}	W = {s["W"]}\n')