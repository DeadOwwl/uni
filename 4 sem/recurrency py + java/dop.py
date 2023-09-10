import numpy as np


def fine(array, nn, mm):
    fine_array = np.zeros((nn, mm), dtype=np.int64)
    fine_array[0] = [i for i in array[0]]
    for l in range(1, nn):
        for k in range(mm):
            fine_array[l][k] = array[l][k] + fine_array[l - 1][k]  # center
            if k > 0 and fine_array[l][k] > array[l][k] + fine_array[l - 1][k - 1]:  # left
                fine_array[l][k] = array[l][k] + fine_array[l - 1][k - 1]
            if k < mm - 1 and fine_array[l][k] > array[l][k] + fine_array[l - 1][k + 1]:  # right
                fine_array[l][k] = array[l][k] + fine_array[l - 1][k + 1]
    return min([i for i in fine_array[nn - 1]])


f = open('input.txt')
line = f.readline()
n, m = [int(i) for i in (line.split())]
ways = np.zeros((n, m), dtype=np.int64)
for i in range(n):
    ways[i] = [int(j) for j in f.readline().split()]
open('output.txt', 'w').write(str(fine(ways, n, m)))
