from __future__ import print_function
import math
import copy
import matplotlib.pyplot as plt
from gamma_functions import *
import numpy as np
import scipy.stats as ss


# считываем с бинарного файла
def read_bits_from_file(file_name, size=-1, blocks_count=1):
    blocks = []

    with open(file_name, 'rb') as file:
        byte = file.read(1)
        res = ''
        if size == -1:
            while byte:
                tmp = format(int.from_bytes(byte, 'little'), 'b')
                tmp = tmp if len(tmp) == 8 else '0' * (8 - len(tmp)) + tmp
                res = res + tmp
                byte = file.read(1)
            blocks.append(res)
        else:
            while blocks_count:
                res = ''
                while byte and len(res) < size:
                    tmp = format(int.from_bytes(byte, 'little'), 'b')
                    tmp = tmp if len(tmp) == 8 else '0' * (8 - len(tmp)) + tmp
                    res = res + tmp
                    byte = file.read(1)
                blocks_count -= 1
                blocks.append(res)

    return blocks


def read_bin_sequence(file_name: str) -> list:
    sequence = []
    with open(file_name, 'rb') as file:
        # исходную последовательность считываем по 4 байта и получаем int'ы
        byte = file.read(4)
        while byte:
            tmp = int.from_bytes(byte, 'little')
            sequence.append(tmp)
            byte = file.read(4)
    return sequence

# формирование битовой матрицы по блокам
def matrix_from_bits(M, Q, bits, blknum):
    m = list()
    for rownum in range(Q):
        row = bits[rownum * M:(rownum + 1) * M]
        m.append(row)
    return m[:]


# вспомогательная функция для определения ранга матрицы
def row_echelon(M, Q, matrix, blknum):
    lm = copy.deepcopy(matrix)

    pivotstartrow = 0
    pivotstartcol = 0
    for i in range(Q):
        # find pivotrow
        found = False
        for k in range(pivotstartrow, Q):
            if lm[k][pivotstartcol] == 1:
                found = True
                pivotrow = k
                break

        if found:
            # Swap with pivot
            if pivotrow != pivotstartrow:
                lm[pivotrow], lm[pivotstartrow] = lm[pivotstartrow], lm[pivotrow]

            # eliminate lower triangle column
            for j in range(pivotstartrow + 1, Q):
                if lm[j][pivotstartcol] == 1:
                    lm[j] = [x ^ y for x, y in zip(lm[pivotstartrow], lm[j])]

            pivotstartcol += 1
            pivotstartrow += 1
        else:
            pivotstartcol += 1

    return lm


# определение ранга матрицы
def _rank(M, Q, matrix, blknum):
    lm = row_echelon(M, Q, matrix, blknum)
    rank = 0
    for i in range(Q):
        nonzero = False
        for bit in lm[i]:
            if bit == 1:
                nonzero = True
        if nonzero:
            rank += 1
    return rank


# Binary matrix rank test
def binary_matrix_rank_test(bits, M=32, Q=32):
    n = len(bits)
    N = int(math.floor(n / (M * Q)))  # Number of blocks
    # print("  Number of blocks %d" % N)
    # print("  Data bits used: %d" % (N * M * Q))
    # print("  Data bits discarded: %d" % (n - (N * M * Q)))

    if N < 38:
        print(" Number of blocks must be greater than 37")
        p = 0.0
        return False, p, None

    r = M
    product = 1.0
    for i in range(r):
        upper1 = (1.0 - (2.0 ** (i - Q)))
        upper2 = (1.0 - (2.0 ** (i - M)))
        lower = 1 - (2.0 ** (i - r))
        product = product * ((upper1 * upper2) / lower)
    FR_prob = product * (2.0 ** ((r * (Q + M - r)) - (M * Q)))

    r = M - 1
    product = 1.0
    for i in range(r):
        upper1 = (1.0 - (2.0 ** (i - Q)))
        upper2 = (1.0 - (2.0 ** (i - M)))
        lower = 1 - (2.0 ** (i - r))
        product = product * ((upper1 * upper2) / lower)
    FRM1_prob = product * (2.0 ** ((r * (Q + M - r)) - (M * Q)))

    LR_prob = 1.0 - (FR_prob + FRM1_prob)

    FM = 0  # Number of full rank matrices
    FMM = 0  # Number of rank -1 matrices
    remainder = 0
    for blknum in range(N):
        block = bits[blknum * (M * Q):(blknum + 1) * (M * Q)]
        # Put in a matrix
        matrix = matrix_from_bits(M, Q, block, blknum)
        # Compute rank
        rank = _rank(M, Q, matrix, blknum)

        if rank == M:  # count the result
            FM += 1
        elif rank == M - 1:
            FMM += 1
        else:
            remainder += 1

    chisq = (((FM - (FR_prob * N)) ** 2) / (FR_prob * N))
    chisq += (((FMM - (FRM1_prob * N)) ** 2) / (FRM1_prob * N))
    chisq += (((remainder - (LR_prob * N)) ** 2) / (LR_prob * N))
    p = math.e ** (-chisq / 2.0)
    success = (p >= 0.01)

    # print("  Full Rank Count  = ", FM)
    # print("  Full Rank -1 Count = ", FMM)
    # print("  Remainder Count = ", remainder)
    # print("  Chi-Square = ", chisq)

    return success, p


def int2patt(n, m):
    pattern = list()
    for i in range(m):
        pattern.append((n >> i) & 1)
    return pattern


# подсчет шаблонов
def countpattern(patt, bits, n):
    thecount = 0
    for i in range(n):
        match = True
        for j in range(len(patt)):
            if patt[j] != bits[i + j]:
                match = False
        if match:
            thecount += 1
    return thecount


def psi_sq_mv1(m, n, padded_bits):
    counts = []
    for i in range(2 ** m):
        pattern = int2patt(i, m)
        count = countpattern(pattern, padded_bits, n)
        counts.append(count)

    psi_sq_m = 0.0
    for count in counts:
        psi_sq_m += (count ** 2)
    psi_sq_m = psi_sq_m * (2 ** m) / n
    psi_sq_m -= n
    return psi_sq_m


# serial Test
def serial_test(bits, patternlen=None):
    n = len(bits)
    if patternlen != None:
        m = patternlen
    else:
        m = int(math.floor(math.log(n, 2))) - 2

        if m < 4:
            print("Error. Not enough data for m to be 4")
            return False, 0, None
        m = 4

    # Step 1
    padded_bits = bits + bits[0:m - 1]

    # Step 2
    psi_sq_m = psi_sq_mv1(m, n, padded_bits)
    psi_sq_mm1 = psi_sq_mv1(m - 1, n, padded_bits)
    psi_sq_mm2 = psi_sq_mv1(m - 2, n, padded_bits)

    delta1 = psi_sq_m - psi_sq_mm1
    delta2 = psi_sq_m - (2 * psi_sq_mm1) + psi_sq_mm2

    P1 = gammaincc(2 ** (m - 2), delta1 / 2.0)
    P2 = gammaincc(2 ** (m - 3), delta2 / 2.0)

    # print("  psi_sq_m   = ", psi_sq_m)
    # print("  psi_sq_mm1 = ", psi_sq_mm1)
    # print("  psi_sq_mm2 = ", psi_sq_mm2)
    # print("  delta1     = ", delta1)
    # print("  delta2     = ", delta2)
    # print("  P1         = ", P1)
    # print("  P2         = ", P2)

    success = (P1 >= 0.01) and (P2 >= 0.01)
    return success, (P1 + P2) / 2


if __name__ == '__main__':
    file_names = ['prop_10.bin', 'prop_20.bin', 'prop_30.bin']
    # sample_data = read_bits_from_file('gamma500.bin', 10 ** 5, 100)

    binary_matrix_rank_results = []
    serial_test_results = []

    num = 0
    for lfsr in file_names:
        lfsr_bin = read_bits_from_file(lfsr, 10**6)
        lfsr_new = []
        for elem in lfsr_bin[0]:
            lfsr_new.append(int(elem))
        pp = len(lfsr)

        res_one = binary_matrix_rank_test(lfsr_new)
        res_two = serial_test(lfsr_new)
        binary_matrix_rank_results.append(res_one[1])
        serial_test_results.append(res_two[1])
        num += 1
        print(num)

    print((0.542704944888395, 0.1942345838))
    print(ss.pearsonr(serial_test_results, np.random.uniform(size=3)))

    plt.hist(binary_matrix_rank_results, bins=10)
    plt.show()
    plt.hist(serial_test_results, bins=10)
    plt.show()
