import numpy as np


def max_score(k, c, j, t, weights, n, n_cards):
    final_cards = np.zeros((k + 1, 2), dtype=np.int64)
    for i in range(k + 1):
        final_cards[i][0] += i
    for i in range(1, len(n_cards)):
        final_cards[n_cards[i]][1] += 1
    jokers_num = final_cards[0][1]
    final_cards = final_cards[np.lexsort((final_cards[:, 1], ))]
    best_cards = np.zeros((t, 2), dtype=np.int64)
    j = 0
    for i in range(k + 1 - t, k + 1):
        best_cards[j] = final_cards[i]
        j += 1
    matrix_cards_score_combination = np.zeros((t, jokers_num + 1), dtype=np.int64)
    for i in range(t):
        for j in range(jokers_num + 1):
            matrix_cards_score_combination[i][j] = (weights[best_cards[i][1] + j], j)
    while True:
        num_adding_jokers_array = [] * t
        for i in range(jokers_num + 1):
            num_adding_jokers_array[i] = sorted(matrix_cards_score_combination[i], key=lambda x: x[1])[1]
        sum_num_adding_jokers = sum(i for i in num_adding_jokers_array)
        if sum_num_adding_jokers == jokers_num:
            break
       # else:

    return


f = open("jokers.in")
line = f.readline()
k_condition, c_condition, j_condition, t_condition = [int(i) for i in line.split()]
line = f.readline()
weights_condition = [int(i) for i in line.split()]
n_condition = int(f.readline())
line = f.readline()
cards_condition = [int(i) for i in line.split()]
open("jokers.out", 'w').write(str(max_score(k_condition, c_condition, j_condition, t_condition, weights_condition, n_condition, cards_condition)))