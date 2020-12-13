import constraint

problem = constraint.Problem()

problem.addVariables("TF", range(1, 10))
problem.addVariables("WOUR", range(10))

def myConstraint(t, f, w, o, u, r):
    if 2 * (t * 100 + w * 10 + o) == 1000 * f + 100 * o + 10 * u + r:
        return True

problem.addConstraint(myConstraint, "TWOFUR")
problem.addConstraint(constraint.AllDifferentConstraint())

results = problem.getSolutions()

for result in results:
    print(f"""
    ---------
      {result["T"]} {result["W"]} {result["O"]}\n
    + {result["T"]} {result["W"]} {result["O"]}\n
    ----------\n
    = {result["F"]} {result["O"]} {result["U"]} {result["R"]}\n
    """)