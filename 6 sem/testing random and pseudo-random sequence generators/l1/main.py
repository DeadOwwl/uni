from scipy.stats import chi2

A = [[4529.4, 9044.9, 13568, 18091, 22615, 27892],
     [9044.9, 18097, 27139, 36187, 45234, 55789],
     [13568, 27139, 40721, 54281, 67582, 83685],
     [18091, 36187, 54281, 72414, 90470, 111580],
     [22615, 45234, 67852, 90470, 113262, 139476],
     [27892, 55789, 83685, 111580, 139476, 172860]]

B = [1/6, 5/24, 11/120, 19/720, 29/5040, 1/840]

chi_square_for_6_degree_of_freedom = {0.995: 0.767,
                                      0.99: 0.872,
                                      0.975: 1.237,
                                      0.95: 1.635,
                                      0.9: 2.204,
                                      0.1: 10.645,
                                      0.05: 12.592,
                                      0.025: 14.449,
                                      0.01: 16.812}

# def igf(S, Z):
#     if Z < 0:
#         return 0
#     Sc = 1.0 / S
#     Sc *= pow(Z, S)
#     Sc *= math.exp(-Z)
#     Sum = 1.0
#     Nom = 1.0
#     Denom = 1.0
#     for _ in range(0, 200):
#         Nom *= Z
#         S += 1
#         Denom *= S
#         Sum += (Nom / Denom)
#     return Sum * Sc
#
#
# def freq(arr):
#     un, counts = np.unique(arr, return_counts=True)
#     return counts / len(arr)
#
#
# def freq_test(arr):
#     fr = freq(arr)
#     fr_exp = [1/len(fr) for _ in range(len(fr))]
#     answ = chisquare(f_obs=fr, f_exp=fr_exp)
#     return answ


def monotonicity_criterion(checking_sequence: list, p: int = 0.05):
    if p not in chi_square_for_6_degree_of_freedom.keys():
        raise ValueError('Invalid p-value.')

    n = len(checking_sequence)
    partitions = []
    previous_i = 0
    for i in range(1, len(checking_sequence)):
        if checking_sequence[i] < checking_sequence[i - 1]:
            partitions.append(checking_sequence[previous_i: i])
            previous_i = i
    counts = [0] * 7

    for sublist in partitions:
        if len(sublist) < 6:
            counts[len(sublist)] += 1
        else:
            counts[6] += 1
    arr = [counts[i] / n for i in range(len(counts))]

    V = 0
    for i in range(1, 7):
        for j in range(1, 7):
            V += (counts[i] - n * B[i - 1]) * (counts[j] - n * B[j - 1]) * A[i - 1][j - 1]
    V *= 1 / (n - 6)

    value = chi2.ppf(V)
    print(value)
    return V, chi_square_for_6_degree_of_freedom[p]


if __name__ == '__main__':
    sequence = list()
    num = 0
    with open('gamma500.bin', 'rb') as binaryFile:
        byte = binaryFile.read(1)
        while byte:
            sequence.append(int.from_bytes(byte, 'little'))
            byte = binaryFile.read(1)
            num += 1
            if num == 10**6:
                break
    result = monotonicity_criterion(sequence)
    print(f'V-statistic: {result[0]}, Chi-square-statistic: {result[1]}')
