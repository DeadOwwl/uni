import heapq


def lazy_dijkstras_min(graph, root):
    n = len(graph)
    if len(graph[root]) != 0:
        dist = [-100_000 for _ in range(n)]
        dist[root] = 0
        visited = [False for _ in range(n)]
        pq = [(1, root)]
        while len(pq) > 0:
            _, u = heapq.heappop(pq)
            if visited[u]:
                continue
            visited[u] = True
            for v, l in graph[u]:
                if len(graph[v]) != 0:
                    if dist[u] + l < dist[v]:
                        dist[v] = dist[u] + l
                        heapq.heappush(pq, (dist[v], v))
        return dist


f = open("input.txt")
w = open("output.txt", 'w')
line = f.readline()
n_condition, m_condition = [int(word) for word in line.split()]
graph_condition = dict((k, []) for k in range(1, n_condition))
for i in range(m_condition):
    line = f.readline().split()
    graph_condition[1].append((1, 2))
    graph_condition[int(line[0]) - 1].append((int(line[1]) - 1, int(line[2])))


distances = []
w.write(str(min(distances)))
