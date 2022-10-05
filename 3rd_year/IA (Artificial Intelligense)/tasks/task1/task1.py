# s --> [(a,2), (e,2)] e --> [(s,2),(f,5)]
# a --> [(s,2), (b,2)] f --> [(e,5),(g,2)]
# b --> [(a,2), (c,2)] g --> [(f,2),(t,2)]
# c --> [(b,2), (d,3)]
# d --> [(c,3), (t,3)]

# right side of the graph has less nodes with a lower cost

# 2 O(|V|) , O(|V|+|E|)

for v in g:
	color[v] = 'WHITE'
	parent[v] = ''

def bf_visit(g, s):
	color[s] = 'GRAY'
	print s, 'GRAY'
	parent[s] = '(ROOT)'
	q.enqueue(s)
	while(not q.isEmpty()):
		u = q.dequeue()
		for v in g[u]: 
			if color[v] == 'WHITE':
				color[v] = 'GRAY'
				print v, 'GRAY'
				parent[v] = u
				q.enqueue(v)
			color[u] = 'BLACK'
			print u, 'BLACK'

def bfs(g):
	for u in g:
		if color[u] == 'WHITE':
			bf_visit(g, u)


# 3  O(|E|) , O(|V|+|E|) could take more if goes for the left side of the graph
def df_visit(g, s):
	color[s] = 'GRAY'
	print s, 'GRAY'
	for v in g[s]:
		if color[v] == 'WHITE':
			parent[v] = s
			df_visit(g, v)
		color[s] = 'BLACK'
		print s, 'BLACK'

def dfs(g):
	for u in g:
		if color[u] == 'WHITE':
			df_visit(g, u)


