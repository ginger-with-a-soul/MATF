from collections import deque

adj_list = {
	'A': ([('B', 20), ('C', 50), ('D', 100)], 105),
	'B': ([('A', 20), ('C', 20), ('E', 110)], 100),
	'C': ([('A', 50), ('B', 20), ('D', 30)], 50),
	'D': ([('A', 100),('C', 30), ('E', 30)], 20),
	'E': ([('B', 110), ('D', 30)], 0)
}

class Graph:
	def __init__(self, adj_list):
		self.adj_list = adj_list
	
	def __str__(self):
		return self.adj_list
	
	def get_neighbour(self, n):
		return self.adj_list[n][0]

	def h(self, n):
		return self.adj_list[n][1]


def a_star(graph, start, end):
	open_list = set([start])
	closed_list = set([])

	parents = {}
	parents[start] = start

	d = {}
	d[start] = 0

	while len(open_list) > 0:
		n = None
		min_dist = float('inf')

		for v in open_list:
			if d[v] + graph.h(v) < min_dist:
				n = v
				min_dist = d[v] + graph.h(v)
		
		if n == None:
			return None
		
		if n == end:
			path = []

			while parents[n] != n:
				path.append(n)
				n = parents[n]
			
			path.append(start)
			path.reverse()
			return path
		
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
	graph = Graph(adj_list)
	print(a_star(graph, 'A', 'E'))