import numpy as np
from numpy import linalg as LA

def f(x):
	return 0.5*(x[0] - 1) ** 2 + (x[0] ** 2 - x[1]) ** 2

def gradient(x):
	return np.array([4 * x[0] * (x[0] ** 2 - x[1]) + x[0] - 1, 2 * (x[1] - x[0] ** 2)])

def hess(x):
	return np.array([
		[12 * x[0] ** 2 - 4 * x[1] + 1, -4 * x[0]],
		[-4 * x[0], 2]
	])

def newtons_gradient_decscend(f, gradient, hess, max_iterations, epsilon, x0):
	x = x0

	for iterations in range(max_iterations):
		x_new = x - np.dot(LA.inv(hess(x)), gradient(x))
		if np.abs(f(x_new) - f(x)) < epsilon:
			break
		x = x_new
	
	converged = iterations != max_iterations
	
	result = {}
	result['converged'] = converged
	result['iterations'] = iterations
	result ['min'] = x_new
	result['f(min)'] = f(x_new)

	return result


if __name__ == "__main__":
	max_iterations = 1000
	epsilon = 0.0001
	x0 = np.array([2, 2])
	print(newtons_gradient_decscend(f, gradient, hess, max_iterations, epsilon, x0))