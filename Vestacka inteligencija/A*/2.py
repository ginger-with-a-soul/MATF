from collections import deque

adj_list = {
	# (X, Y, cost), (neighbours)
	'S': ((2, 0, 0), ('E', 'Y', 'D')),
	'E': ((3, 0, 1), ('F', 'S')),
	'F': ((4 ,0, 1), ('E', 'G')),
	'G': ((4, 1, 1), ('F', 'H')), 
	'H': ((4, 2, 1), ('G', 'I')),
	'I': ((3, 2, 1), ('H', 'J')),
	'J': ((2, 2, 1), ('Y', 'I', 'C')),
	'C': ((1, 2, 1), ('J', 'A')),
	'A': ((0, 2, 6), ('C', 'B')),
	'B': ((0, 1, 1), ('A', 'X')),
	'X': ((0, 0, 1), ('B', 'D')),
	'D': ((1, 0, 1), ('S', 'X')),
	'Y': ((2, 1, 5), ('S', 'J'))
}

class Graph:
	
	def __init__(self, ajd_list):
		self.adj_list = adj_list

	def __str__(self):
		return self.adj_list
	
	def get_neighbour(self, n):
		return self.adj_list[n]

	def h(self, n, m):
		return abs(self.adj_list[n][0][0] - g.adj_list[m][0][0]) + abs(g.adj_list[n][0][1] - \
																	   g.adj_list[m][0][1])

def astar(g, start, end):
	open_list = set([start])
	closed_list = set([])

	parents = {}
	parents[start] = start

	distances = {}
	distances[start] = 0

	while len(open_list) > 0:

		n = None
		min_distance = float('inf')

		# pronalazi trenutno najblizi cvor pocetnom cvoru
		# u prvom koraku prodje n == None i nase n postane v
		# i azurira min_distance (ova if provera je potrebna)
		# ako se dogodi da je open_list prazna pa da ne bismo
		# trazili Menhetn od None
		# a zatim se provrti kroz celu otvorenu listu i nadje
		# najblizi cvor
		for v in open_list:
			if distances[v] + g.h('C', v) < min_distance:
				n = v
				min_distance = distances[v] + g.h('C', v)

		# ako udje unutra znaci da put nije nadjen
		if n == None:
			return None

		if n == end:
			res = []

			while parents[n] != n:
				res.append(n)
				n = parents[n]

			res.append(start)
			res.reverse()

			return res

		neighbour = g.get_neighbour(n)
		for m in neighbour[1]:
			cost = g.adj_list[m][0][2]
			if m not in open_list and m not in closed_list:
				distances[m] = distances[n] + cost
				parents[m] = n
				open_list.add(m)
			else:
				if distances[m] > distances[n] + cost:
					distances[m] = distances[n] + cost
					parents[m] = n

					if m in closed_list:
						closed_list.remove(m)
						open_list.add(m)
		
		open_list.remove(n)
		closed_list.add(n)

	return None


if __name__ == "__main__":
	g = Graph(adj_list)

	print(astar(g, 'S', 'C'))