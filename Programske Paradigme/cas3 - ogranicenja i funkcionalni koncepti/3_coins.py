import constraint

problem = constraint.Problem()

problem.addVariable("1 din", range(1, 51))
problem.addVariable("2 din", range(1, 26))
problem.addVariable("5 din", range(1, 11))
problem.addVariable("10 din", range(1, 6))
problem.addVariable("20 din", range(1, 3))

problem.addConstraint(constraint.ExactSumConstraint(50, [1, 2, 5, 10, 20]), ["1 din", "2 din", "5 din", "10 din", "20 din"])

results = problem.getSolutions()

for result in results:
    print(f'1 din: {result["1 din"]}, 2 din: {result["2 din"]}, 5 din: {result["5 din"]}, 10 din: {result["10 din"]}, 20 din: {result["20 din"]}')