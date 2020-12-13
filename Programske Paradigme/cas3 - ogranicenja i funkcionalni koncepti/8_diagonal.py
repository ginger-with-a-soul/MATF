import constraint

problem = constraint.Problem()
variables = ["X1", "X2", "X3", "X4", "X5", "X6", "X7", "X8", "X9"]
problem.addVariables(variables, range(1, 10))

def rising(*xs):
	X = [xs]
	for x, y in X:
		if x > y:
			return False
	return True

problem.addConstraint(constraint.AllDifferentConstraint())
problem.addConstraint(lambda X1, X2, X3, X4, X5: X1 + X2 + X3 + X4 + X5 == 25, ["X1", "X2", "X3", "X4", "X5"])
problem.addConstraint(lambda X6, X7, X3, X8, X9: X6 + X7 + X3 + X8 + X9 == 25, ["X6", "X7", "X3", "X8", "X9"])
problem.addConstraint(lambda X1, X2, X3, X4, X5: X1 < X2 and X2 < X3 and X3 < X4 and X4 < X5, ["X1", "X2", "X3", "X4", "X5"])
problem.addConstraint(lambda X6, X7, X3, X8, X9: X6 < X7 and X7 < X3 and X3 < X8 and X8 < X9, ["X6", "X7", "X3", "X8", "X9"])

s = problem.getSolutions()

for r in s:
	print(r)