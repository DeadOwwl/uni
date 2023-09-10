def dfs(v, visited, graph):
    visited[v] = True
    for u in graph[v]:
        if not visited[u]:
            dfs(u, visited, graph)


def components_counting(n, q, graph):
    visited = [False] * n
    count = 0
    for v in range(n):
        if visited[v] is False:
            dfs(v, visited, graph)
            count += 1
    return count


f = open("input.txt")
w = open("output.txt", 'w')
line = f.readline().split()
n_condition, q_condition = [int(i) for i in line]
graph_condition = [[] for i in range(n_condition)]
components = [0] * q_condition
for i in range(q_condition):
    line = f.readline().split()
    a, b = [int(j) for j in line]
    graph_condition[a - 1].append(b - 1)
    graph_condition[b - 1].append(a - 1)
    components[i] = components_counting(n_condition, q_condition, graph_condition)
for i in range(q_condition):
    w.write(str(components[i]) + '\n')
