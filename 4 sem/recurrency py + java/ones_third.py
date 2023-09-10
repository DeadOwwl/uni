import numpy as np


def C(n, k):
    if n < k or k < 0:
        return 0
    if k == 0 or k == n:
        return 1
    c = np.zeros((n + 1, n + 1), dtype = np.int64)
    for i in range(n + 1):
        c[i, 0] = 1
        c[i, i] = 1
        for j in range(1, i):
            c[i, j] = c[i - 1][j] + c[i - 1][j - 1]
    return c[n, k]


def binary_places(number):
    places_array = np.array([], dtype=np.int64)
    place = 0
    while number > 0:
        if number & 1 == 1:
            places_array = np.append(places_array, place)
        number = number >> 1
        place = place + 1
    return sorted(places_array, reverse=True)


def possible_ones_places(p_a, q):
    count = np.int64(0)
    for i in range(len(p_a)):
        count = count + C(p_a[i], q - i)
    return count


line = open('input.txt').readline()
a = int(line.split()[0])
a_binary_ones_places = binary_places(a)
b = int(line.split()[1]) + 1
b_binary_ones_places = binary_places(b)
k_b = int(line.split()[2])
a_binary_ones_possibility = possible_ones_places(a_binary_ones_places, k_b)
b_binary_ones_possibility = possible_ones_places(b_binary_ones_places, k_b)
answer = np.int64(b_binary_ones_possibility - a_binary_ones_possibility)
open('output.txt', 'w').write(str(answer))
