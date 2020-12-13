import constraint

problem = constraint.Problem()

problem.addVariable('X', range(1, 11))
domain_Y = []
domain_Z = []
domain_W = []

for i in range(1, 52):
    domain_Y.append(i)
    i += 2

problem.addVariable('Y', domain_Y)

for i in range(1, 11):
    domain_Z.append(i * 10)
    domain_W.append(i ** 3)

problem.addVariable('Z', domain_Z)
problem.addVariable('W', range(1, 101))

problem.addConstraint(lambda x, w: x >= 2 * w, 'XW')
problem.addConstraint(lambda z, y: z >= y + 3, 'ZY')
problem.addConstraint(lambda x, y, z, w: x - 11 * w + y + 11 * z <= 100, 'XYZW')

results = problem.getSolutions()

for result in results:
    print(f'X = {result["X"]}, Y = {result["Y"]}, Z = {result["Z"]}, W = {result["W"]}')