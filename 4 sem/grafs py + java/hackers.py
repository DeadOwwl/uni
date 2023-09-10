def dfs(v, used_dfs, graph_dfs, is_transposed, c):
    if used_dfs[v]:
        return
    used_dfs[v] = True
    if is_transposed:
        vertexes_components[v] = c
    for i in range(len(graph_dfs[v])):
        u = graph_dfs[v][i]
        if not used_dfs[u]:
            dfs(u, used_dfs, graph_dfs, is_transposed, c)
    if not is_transposed:
        order.append(v)


def defining(n, graph, transposed_graph, terminals, components):
    ans = []
    for i in range(n):
        if not used[i]:
            dfs(i, used, graph, False, components)
    order.reverse()
    for i in range(len(order)):
        v = order[i]
        if vertexes_components[i] == -1:
            dfs(v, used_transposed, transposed_graph, True, components)
            components += 1
    k_comp = max(vertexes_components) + 1
    component_array = [[] for i in range(k_comp)]
    for i in range(len(vertexes_components)):
        component_array[vertexes_components[i]].append(i)
    min_vertexes = []
    for i in range(k_comp):
        min_comp_vert = component_array[i][0]
        min_comp_terminals = terminals[min_comp_vert]
        our_vertex = min_comp_vert
        for j in range(len(component_array[i])):
            st_term = component_array[i][j]
            if min_comp_terminals > terminals[st_term]:
                our_vertex = st_term
                min_comp_terminals = terminals[st_term]
        min_vertexes.append(our_vertex)
    order.clear()
    for i in range(n):
        used[i] = False
    for i in range(len(min_vertexes)):
        v = min_vertexes[i]
        if not used[v]:
            ans.append(v + 1)
            dfs(v, used, graph, False, 0)
    return ans


f = open("input.txt", 'r')
w = open("output.txt", 'w')
n_condition = int(f.readline())
graph_condition = [[] * n_condition for i in range(n_condition)]
transposed_graph_condition = [[] * n_condition for i in range(n_condition)]
terminals_condition = []
for i in range(n_condition):
    terminals_condition.append(int(f.readline()))
for i in range(n_condition + 1):
    line = f.readline().split()
    u, v = [int(i) for i in line]
    graph_condition[u - 1].append(v - 1)
    transposed_graph_condition[v - 1].append(u - 1)
used = [False] * n_condition
used_transposed = [False] * n_condition
vertexes_components = [-1] * n_condition
order = []
components_condition = 0
answer = defining(n_condition, graph_condition, transposed_graph_condition, terminals_condition, components_condition)
w.write(str(len(answer)) + '\n')
for i in answer:
    w.write(str(i) + ' ')
