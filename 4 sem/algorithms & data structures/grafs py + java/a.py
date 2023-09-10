# bfs
def time_finding(n, dominoes):
    bfs_queue = []
    checked_vertexes = 0
    for k in range(n):
        visited = [False if q != k else True for q in range(n)]
        bfs_queue.insert(0, k)
        while len(bfs_queue) != 0:
            checking_current_vertex = bfs_queue.pop()
            for adjacent_vertex in dominoes[checking_current_vertex]:
                if not visited[adjacent_vertex]:
                    bfs_queue.insert(0, adjacent_vertex)
                    checked_vertexes += 1
                    visited[adjacent_vertex] = True
    return checked_vertexes


f = open("input.in")
w = open("output.out", 'w')
n_condition = int(f.readline())
dominoes_condition = []
for i in range(n_condition):
    line = f.readline().split()
    m_condition = int(line[0])
    list_condition = []
    for j in range(1, m_condition + 1):
        list_condition.append(int(line[j]) - 1)
    dominoes_condition.append(list_condition)
answer = time_finding(n_condition, dominoes_condition)
if answer == n_condition:
    w.write("YES")
else:
    w.write("NO")