from functools import reduce
import numpy as np
import matplotlib.pyplot as plt


def write(txt: str, binary: str, values: list, last=8):
    def chunks(l, n):
        n = max(1, n)
        return (l[i:i + n] for i in range(0, len(l), n))

    bits = "".join([bin(i).replace('0b', '')[-last:] for i in values])

    with open(txt, 'w') as out1, open(binary, 'wb') as out2:
        out1.write(bits)
        for b in [(int("0b" + i, base=2).to_bytes(1, byteorder='big')) for i in chunks(bits, 8)]:
            out2.write(b)


def scatter_show(x: list, y: list):
    fig, ax = plt.subplots(figsize=(10, 6))
    ax.scatter(x, y)
    plt.show()


def lcg(a: int, x: int, c: int, M: int, unit: int) -> list:
    result = []
    for _ in range(unit):
        rd = (a * x + c) % M
        x = rd
        result.append(x)
    return result


def lfsr(seed_inside: list, mask_inside: list):
    while True:
        s = sum([i * j for i, j in zip(seed_inside, mask_inside)]) % 2
        yield s
        seed_inside = [*seed_inside[1:], s]


def main_lfsr(seed_lfsr: list, mask_lfsr: list, count) -> list:
    lfsr_result = lfsr(seed_lfsr, mask_lfsr)
    return [next(lfsr_result) for _ in range(count)]


def main_shrinking_generator(seed_one: list, mask_one: list,
                             seed_two: list, mask_two: list, count) -> list:
    def shrinking_generator(second_result_inside, first_result_inside):
        last = next(second_result_inside)
        last2 = next(first_result_inside)
        while True:
            while last != 1:
                last = next(second_result_inside)
                last2 = next(first_result_inside)
            yield last2
            last = 0

    shrinking_result = shrinking_generator(lfsr(seed_one, mask_one),
                                           lfsr(seed_two, mask_two))
    return [next(shrinking_result) for _ in range(count)]


def getA(m):

    def deliteli(val):
        return [*filter(lambda x: val % x == 0, range(1, val // 2 + 1)), val]

    def isSimple(val):
        return val == 1 or len(deliteli(val)) == 2

    sd = list(filter(lambda x: isSimple(x), deliteli(m)))
    b = reduce(lambda a, x: a * x, sd)
    if m % 4 == 0 and b % 4 != 0:
        b *= 4

    return b + 1


if __name__ == '__main__':

    # 1.
    M_condition = 91
    a_condition = getA(M_condition)
    x0_condition, c_condition, unit_condition = 79, 73, 1_000_000
    result_first = lcg(a_condition, x0_condition,
                       c_condition, M_condition, unit_condition)

    scatter_show(result_first[:len(result_first) - 1],
                 result_first[1:])

    write('first.txt', 'first.bin', result_first)

    # 2.
    x0_condition = 79
    i_condition = 12
    p_i_condition = 10103
    # M_condition = 2 ** 20 + i_condition * p_i_condition
    M_condition = 10_836
    a_condition = 2**2 * 3 * 7 * 43 + 1
    c_condition = 13
    # c_condition = getA(M_condition)
    result_second = lcg(a_condition, x0_condition,
                        c_condition, M_condition, unit_condition)

    scatter_show(result_second[:len(result_second) - 1],
                 result_second[1:])

    write('second.txt', 'second.bin', result_second)

    # # 3.
    # size_of_int = 8
    # n = 2**15 * 8
    #
    # seed_f = [1, 0, 1, 0, 1]
    # mask_f = [1, 0, 0, 1, 0]
    # third_result = main_lfsr(seed_f, mask_f, n)
    #
    # grouped_bites = [third_result[i:i + size_of_int]
    #                  for i in range(0, len(third_result), size_of_int)]
    # string_bytes = ['0b' + ''.join(str(i) for i in element)
    #                 for element in grouped_bites]
    # third_int_result = [int(i, base=2) for i in string_bytes]
    #
    # scatter_show(third_int_result[:len(third_int_result) - 1],
    #              third_int_result[1:])
    #
    # write('third.txt', 'third.bin', third_result)
    #
    # # 4.
    # seed_t = [1, 1, 0, 0, 1, 0, 1, 1, 0, 1]
    # mask_t = [1, 1, 1, 0, 1, 0, 0, 1, 0, 1]
    # fourth_result = main_lfsr(seed_t, mask_t, n)
    #
    # grouped_bites = [fourth_result[i:i + size_of_int]
    #                  for i in range(0, len(fourth_result), size_of_int)]
    # string_bytes = ['0b' + ''.join(str(i) for i in element)
    #                 for element in grouped_bites]
    # fourth_int_result = [int(i, base=2) for i in string_bytes]
    #
    # scatter_show(fourth_int_result[:len(fourth_int_result) - 1],
    #              fourth_int_result[1:])
    #
    # write('fourth.txt', 'fourth.bin', fourth_result)
    #
    # # 5.
    # fifth_result = main_shrinking_generator(seed_f, mask_f,
    #                                         seed_t, mask_t, n)
    #
    # grouped_bites = [fifth_result[i:i + size_of_int]
    #                  for i in range(0, len(fifth_result), size_of_int)]
    # string_bytes = ['0b' + ''.join(str(i) for i in element)
    #                 for element in grouped_bites]
    # fifth_int_result = [int(i, base=2) for i in string_bytes]
    #
    # scatter_show(fifth_int_result[:len(fifth_int_result) - 1], fifth_int_result[1:])
    #
    # write('fifth.txt', 'fifth.bin', fifth_result)
