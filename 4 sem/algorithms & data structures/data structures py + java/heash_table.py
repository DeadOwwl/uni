def cells_checking(m, c, n, keys):
    hash = [-1] * m
    for i_m in range(n):
        is_there = False
        for i in range(m):
            if hash[i] == keys[i_m]:
                is_there = True
        if not is_there:
            for i in range(m):
                address = (keys[i_m] % m + c*i) % m
                if hash[address] == -1:
                    hash[address] = keys[i_m]
                    break
    return hash


f = open("input.txt")
w = open("output.txt", 'w')
line = f.readline()
m_condition, c_condition, n_condition = [int(i) for i in line.split()]
keys_condition = []
for i in range(n_condition):
    keys_condition.append(int(f.readline()))
answer = cells_checking(m_condition, c_condition, n_condition, keys_condition)
for i in answer:
    w.write(str(i) + ' ')
