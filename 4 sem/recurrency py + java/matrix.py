import numpy as np


def matrix_optimal_multiplication(sizes_fun):
    n = len(sizes_fun)
    result_matrix = np.zeros((n, n))
    for l in range(2, n):
        for i in range(1, n - l + 1):
            j = i + l - 1
            result_matrix[i][j] = float('Inf')
            for k in range(i, j):
                cost = result_matrix[i][k] + result_matrix[k + 1][j] + sizes_fun[i - 1] * sizes_fun[k]
                if cost < result_matrix[i][j]:
                    result_matrix[i][j] = cost
    return int(result_matrix[1][n - 1])


f = open('input.txt')
w = open('output.txt', 'w')
line = f.readline()
s = int(line)
sizes = []
for i in range(s):
    line = f.readline()
    sizes.append(int(line.split(' ')[0]))
    if i is s - 1:
        sizes.append(int(line.split(' ')[1]))
w.write(str(matrix_optimal_multiplication(sizes)))
