def bfs(n, graph):
    another_visit = [0] * n
    visited = [False] * n
    queue = []
    times = 0
    for i in range(n):
        if not visited[i]:
            queue.append(i)
        visited[i] = True
        while len(queue) != 0:
            s = queue.pop(0)
            another_visit[s] = times + 1
            times += 1
            for j in range(n):
                if graph[s][j] == 1 and not visited[j]:
                    queue.append(j)
                    visited[j] = True
    return another_visit


f = open("input.txt")
w = open("output.txt", 'w')
n_condition = int(f.readline())
graph_condition = [[] * n_condition for i in range(n_condition)]
for i in range(n_condition):
    line = f.readline().split()
    graph_condition[i] = [int(line[k]) for k in range(n_condition)]
answer = bfs(n_condition, graph_condition)
for i in range(n_condition):
    w.write(str(answer[i]) + ' ')
