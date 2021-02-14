from collections import deque

adj_list = {
	'A': [('B', 10), ('C', 1)],
	'C': [('B', 8), ('D', 1), ('A', 1)],
	'D': [('B', 6), ('E', 1), ('C', 1)],
	'E': [('B', 4), ('D', 1)],
	'B': [('A', 10), ('C', 8), ('D', 6), ('E', 4)]
}

class Graph:

	def __init__(self, ajd_list):
		self.adj_list = ajd_list

	def __str__(self):
		return self.adj_list

	def get_neighbour(self, n):
		return self.adj_list[n]
	
	def h(self, n):
		return 1

def astar(graph, start, end):
	open_list = set([start])
	closed_list = set([])

	parents = {}
	parents[start] = start

	d = {}
	d[start] = 0

	while len(open_list) > 0:

		n = None
		min_dist = float('inf')

		# komentar za ovo pogledati u zadatku 2.py
		for v in open_list:
			if d[v] + graph.h(v) < min_dist:
				n = v
				min_dist = d[v] + graph.h(v)

		if n == None:
			return None

		if n == end:
			result = []
			
			while parents[n] != n:
				result.append(n)
				n = parents[n]
			
			result.append(start)
			result.reverse()

			return result
		
		for (m, cost) in graph.get_neighbour(n):

			if m not in open_list and m not in closed_list:
				d[m] = d[n] + cost
				parents[m] = n
				open_list.add(m)
			else:
				if d[m] > d[n] + cost:
					d[m] = d[n] + cost
					parents[m] = n

					if m in closed_list:
						closed_list.remove(m)
						open_list.add(m)
		
		open_list.remove(n)
		closed_list.add(n)

	return None

if __name__ == "__main__":
	g = Graph(adj_list)
	print(astar(g, 'A', 'B'))