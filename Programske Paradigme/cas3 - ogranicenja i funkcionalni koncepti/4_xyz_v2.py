import constraint

problem = constraint.Problem()

problem.addVariable('X', range(1, 91))
problem.addVariable('Y', range(2, 61, 2))
domain_Z = []

for i in range(1, 11):
    domain_Z.append(i * i)

problem.addVariable('Z', domain_Z)


problem.addConstraint(lambda X, Z: X >= Z, ['X', 'Z'])
problem.addConstraint(lambda X, Y, Z: X * 2 + Y * X + Z <= 34, ['X', 'Y', 'Z'])

results = problem.getSolutions()

for result in results:
    print(f'X = {result["X"]}, Y = {result["Y"]}, Z = {result["Z"]}')