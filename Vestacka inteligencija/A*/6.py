adj_list = {
		# pair where first is list of neighbours with
		# cost to reach them and 2nd is heuristic cost
	'S': ([('A', 2), ('C', 2), ('D', 2)], 2),
	'A': ([('S', 2), ('B', 2), ('C', 2)], 2),
	'B': ([('A', 2), ('F', 2)], 1),
	'C': ([('S', 2), ('A', 2), ('D', 6), ('F', 6)], 1),
	'D': ([('S', 2), ('C', 6), ('F', 6)], 1),
	'F': ([('C', 6), ('D', 6), ('B', 2)], 0)
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

def astar(g, start, end):
	
	open_list = set([start])
	closed_list = set([])
	
	parents = {}
	parents[start] = start

	dist = {}
	dist[start] = 0

	while len(open_list) > 0:
		
		n = None
		min_dist = float('inf')

		for v in open_list:
			if dist[v] + g.h(v) < min_dist:
				n = v
				min_dist = dist[v] + g.h(v)
		
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
		
		for (m, cost) in g.get_neighbour(n):
			if m not in open_list and m not in closed_list:
				dist[m] = dist[n] + cost
				parents[m] = n
				open_list.add(m)
			else:
				if dist[m] > dist[n] + cost:
					dist[m] = dist[n] + cost
					parents[m] = n

					if m in closed_list:
						closed_list.remove(m)
						open_list.add(m)
		
		open_list.remove(n)
		closed_list.add(n)
	
	return None
		


if __name__ == "__main__":
	g = Graph(adj_list)
	print(astar(g, 'S', 'F'))