def checking(n, graph):
    for i in range(n):
        if not visited[i]:
            dfs(i, n)


def dfs(v, n):
    visited[v] = True
    another_visit[v] = time_checking + 1
    time_checking += 1

    return


f = open("input.txt")
w = open("output.txt", 'w')
n_condition = int(f.readline())
graph_condition = [[] * n_condition for i in range(n_condition)]
for i in range(n_condition):
    line = f.readline().split()
    graph_condition[i] = [int(line[k]) for k in range(n_condition)]
visited = [False] * n_condition
time_checking = 0
another_visit = [0] * n_condition
answer = dfs(n_condition, graph_condition)
for i in range(n_condition):
    w.write(str(answer[i]) + ' ')
