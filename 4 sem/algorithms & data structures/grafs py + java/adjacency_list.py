f = open("input.txt")
w = open("output.txt", 'w')
line = f.readline().split()
n_condition, m_condition = [int(i) for i in line]
adj_list = [[] for i in range(n_condition)]
for i in range(m_condition):
    line = f.readline().split()
    a, b = [int(j) for j in line]
    adj_list[a - 1].append(b)
    adj_list[b - 1].append(a)
for i in range(n_condition):
    w.write(str(len(adj_list[i])) + ' ')
    for j in range(len(adj_list[i])):
        w.write(str(adj_list[i][j]) + ' ')
    w.write('\n')
