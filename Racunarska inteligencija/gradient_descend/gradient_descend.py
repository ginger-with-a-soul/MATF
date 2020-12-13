import numpy as np

def gradient_descend(f, x0, gradient, max_iterations, alpha, epsilon):
	x = x0

	for iteration in range(max_iterations):
		x_new = x - alpha * gradient(x)

		if abs(f(x_new) - f(x)) < epsilon:
			break

		x = x_new

	converged = iteration != max_iterations

	result = {}
	result['converged'] = converged
	result['min'] = x_new
	result['iterations'] = iteration
	result['f(min)'] = f(x_new)

	return result

def f(x):
	return 0.5 * (x[0] ** 2 + 10 * x[1] ** 2)

def gradient(x):
	return np.array(x[0], 10 * x[1])

if __name__ == "__main__":
	alpha = 0.1
	max_iterations = 1000
	epsilon = 0.01
	x0 = np.array([3, 5])
	
	print(gradient_descend(f, x0, gradient, max_iterations, alpha, epsilon))
