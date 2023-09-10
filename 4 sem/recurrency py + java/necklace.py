import math
import numpy as np


def pow_division(n_pd):
    result = 1
    degree = module - 2
    while degree != 0:
        if degree & 1:
            result = (result * n_pd) % module
        n_pd = (n_pd * n_pd) % module
        degree >>= 1
    return result


def C(n_c, k_c):
    a1 = 1
    a2 = 1
    for i in range(n_c, n_c - k_c):
        a1 *= i
        a1 %= module
    for i in range(k_c, 1):
        a2 *= i
        a2 %= module
    return (a1 * pow_division(a2)) % module


def assembly_number_methods(n, k, stones_colors):
    comb = np.zeros((k, k), dtype=np.int64)
    comb[stones_colors[0]][0] = math.factorial(stones_colors[0] - 1)
    sum_fst = np.zeros(k, dtype=np.int64)
    sum_fst = stones_colors[0]
    for l in range(1, k):
        sum_fst[l] = sum_fst[l-1]+stones_colors[l]
    for l in range(1, k):
        for j in range(sum_fst[k - 1]):
            comb[j][l] = 0
        for k in range(sum_fst[l] + 1):
            comb[k][l] = 0
            for i in range(sum_fst[l] + 1):
                to_add = 0
                for div in (1, stones_colors[l] + 1):
                    if 0 <= i + stones_colors[l] - div - k <= i and 0 <= div - (i + stones_colors[l] - div - k) <= \
                            sum_fst[l - 1] - i:
                        to_add = (to_add + ((((C[i][i + stones_colors[l] - div - k] * C[sum_fst[l - 1] - i][
                            div - (i + stones_colors[l] - div - k)]) % module *
                                              math.factorial(stones_colors[l])) % module) * C[stones_colors[l] - 1][stones_colors[l] - div]) % module) % module
                to_add = (to_add * comb[i][l - 1]) % module
                comb[k][l] = (comb[k][l] + to_add) % module
    return (comb[0][k - 1] * (sum_fst[k - 1])) % module


module = 1000000007
f = open("necklace.in")
line = f.readline()
n_condition, k_condition = [int(i) for i in (line.split())]
stones_colors_condition = np.zeros(n_condition, dtype=np.int64)
for i in range (n_condition):
    stones_colors_condition[i] = int(f.readline())
open("necklace.out", 'w').write(str(assembly_number_methods(n_condition, k_condition, stones_colors_condition)))
