readingFile = open("in.txt")
n = int(readingFile.readline())
graph = []
for i in range(n):
    line = readingFile.readline().split()
    m = int(line[0])
    a_string = []
    for j in range(1, m + 1):
        a_string.append(int(line[j]) - 1)
    graph.append(a_string)

main_queue = []
for_time = [None] * n
is_possible = False
max_time = -1
final_start_vertex = -1

for k in range(n):
    local_max_time = 0
    visited = [False if q != k else True for q in range(n)]
    for_time[k] = 0
    main_queue.insert(0, k)
    checked_vertexes = 1
    while len(main_queue) != 0:
        checking_current_vertex = main_queue.pop()
        for adjacent_vertex_index in range(len(graph[checking_current_vertex])):
            if not visited[graph[checking_current_vertex][adjacent_vertex_index]]:
                main_queue.insert(0, graph[checking_current_vertex][adjacent_vertex_index])
                checked_vertexes += 1
                visited[graph[checking_current_vertex][adjacent_vertex_index]] = True
                for_time[graph[checking_current_vertex][adjacent_vertex_index]] = for_time[checking_current_vertex] + 1
                local_max_time = max(for_time[graph[checking_current_vertex][adjacent_vertex_index]], local_max_time)
    if checked_vertexes == n:
        is_possible = True
        if local_max_time >= max_time:
            max_time = local_max_time
            final_start_vertex = k
open("out.txt", 'w').write(str(max_time) + '\n' + str(final_start_vertex + 1)) if is_possible else open("out.txt", 'w').write("impossible")
