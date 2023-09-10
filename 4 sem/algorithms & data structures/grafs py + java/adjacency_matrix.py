f = open("input.txt")
w = open("output.txt", 'w')
line = f.readline().split()
v_condition, e_condition = [int(i) for i in line]
graph_condition = [[0] * v_condition for i in range(v_condition)]
for i in range(e_condition):
    line = f.readline().split()
    a, b = [int(j) for j in line]
    graph_condition[a - 1][b - 1] = 1
    graph_condition[b - 1][a - 1] = 1
for i in range(v_condition):
    for j in range(v_condition):
        w.write(str(graph_condition[i][j]) + ' ')
    if i != v_condition - 1:
        w.write('\n')
