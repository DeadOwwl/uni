import heapq


def calculate_distances(graph, starting_vertex):

    return


f = open("input.txt", 'r')
w = open("output.txt", 'w')
line = f.readline().split()
n_condition, m_condition = [int(i) for i in line]
graph = [[] * n_condition for i in range(n_condition)]
for i in range(m_condition):
    line = f.readline().split()
    u, v, c = [int(i) for i in line]
    graph[u - 1].append((v - 1, c))
    graph[v - 1].append((u - 1, c))
s = 0
d = [float('inf')] * n_condition
d[0] = 0
p = [0] * n_condition
q = set()
q.add((d[s], s))
while len(q) != 0:
    v = q.pop()[1]
    for elem in graph[v]:
        to, length = elem
        if d[v] + length < d[to]:
            q.remove((d[to], to))
            d[to] = d[v] + length
            p[to] = v
            q.add((d[to], to))
w.write(str(d[n_condition - 1]))