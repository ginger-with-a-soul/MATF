import constraint

problem = constraint.Problem()

problem.addVariable('a', range(1, 10))
problem.addVariable('b', range(10))
problem.addVariable('c', range(10))

problem.addConstraint(constraint.AllDifferentConstraint())

min_solution = {}
min = 999

results = problem.getSolutions()

for result in results:
    a = result['a']
    b = result['b']
    c = result['c']
    current_min = (a * 100 + b * 10 + c) / (a + b + c)
    if current_min < min:
        min = current_min
        min_solution = result

print(f'{min_solution["a"]} * 100 + {min_solution["b"]} * 10 + {min_solution["c"]}')