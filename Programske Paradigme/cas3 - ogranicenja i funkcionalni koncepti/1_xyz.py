import constraint

problem = constraint.Problem()

problem.addVariable('x', ['a', 'b', 'c'])
problem.addVariable('y', [1, 2, 3])
problem.addVariable('z', [0.1, 0.2, 0.3])

def limit(y, z):
    if y / 10 == z:
        return True

problem.addConstraint(limit, ['y', 'z'])
results = problem.getSolutions()

for result in results:
    print(str(f'{result["x"]} {result["y"]} {result["z"]}'))