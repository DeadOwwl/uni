import numpy as np


def ways_num(t, parameters):
    base = 1000000007
    results = np.zeros(t, dtype=np.int64)
    for i in range(t):
        poss = np.zeros(parameters[i][0], dtype=np.int64)
        poss[0] = 1
        between = 1
        for j in range(1, parameters[i][0]):
            poss[j] = between
            between = (poss[j] + between) % base
            if j - parameters[i][1] >= 0:
                between = (between - poss[j - parameters[i][1]] + base) % base
        results[i] = poss[parameters[0][i] - 1]
    return results


poss = open("input.txt")
w = open("output.txt", 'w')
t_condition = int(poss.readline())
parameters_condition = np.zeros((t_condition, 2), dtype=np.int64)
for i in range(t_condition):
    parameters_condition[i] = [int(j) for j in poss.readline().split()]
answer = ways_num(t_condition, parameters_condition)
for i in answer:
    w.write(str(i) + '\n')
