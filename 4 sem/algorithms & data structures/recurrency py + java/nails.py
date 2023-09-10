import numpy as np


def minimal_summary_rope_length(n, coordinates):
    possible_length = np.zeros(n - 1)
    possible_length[0] = coordinates[1] - coordinates[0]
    possible_length[1] = possible_length[0] + coordinates[2] - coordinates[1]
    for i in range(2, n - 1):
        possible_length[i] = min(possible_length[i - 1] + coordinates[i + 1] - coordinates[i],
                                 possible_length[i - 2] + coordinates[i + 1] - coordinates[i])
    return possible_length[n - 2]


f = open("input.txt")
n_condition = int(f.readline())
coordinates_condition = [float(i) for i in f]
open("output.txt", 'w').write("%.2f" % minimal_summary_rope_length(n_condition, coordinates_condition))
# input = in, output = out
