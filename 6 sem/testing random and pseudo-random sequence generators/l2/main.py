import scipy.stats as ss
import numpy as np
from random import randint
import math
from numba import jit
from numba import float32
from numba.experimental import jitclass
import warnings
import scipy.special as spc
warnings.filterwarnings("ignore")
stat = 'KstestResult(statistic=0.18335124956678628, pvalue=0.00000030069256017)'

def overlapping_test(bin_data):
    def get_pik_value(k, x):
        """
        This method is used by the random_excursions method to get expected probabilities
        """
        if k == 0:
            out = 1 - 1.0 / (2 * np.abs(x))
        elif k >= 5:
            out = (1.0 / (2 * np.abs(x))) * (1 - 1.0 / (2 * np.abs(x))) ** 4
        else:
            out = (1.0 / (4 * x * x)) * (1 - 1.0 / (2 * np.abs(x))) ** (k - 1)
        return out

    int_data = np.zeros(len(bin_data))
    for i in range(len(bin_data)):
        if bin_data[i] == '0':
            int_data[i] = -1.0
        else:
            int_data[i] = 1.0

            # Calculate the cumulative sum
    cumulative_sum = np.cumsum(int_data)
    # Append a 0 to the end and beginning of the sum
    cumulative_sum = np.append(cumulative_sum, [0])
    cumulative_sum = np.append([0], cumulative_sum)

    # These are the states we are going to look at
    x_values = np.array([-4, -3, -2, -1, 1, 2, 3, 4])

    # Identify all the locations where the cumulative sum revisits 0
    position = np.where(cumulative_sum == 0)[0]
    # For this identify all the cycles
    cycles = []
    for pos in range(len(position) - 1):
        # Add this cycle to the list of cycles
        cycles.append(cumulative_sum[position[pos]:position[pos + 1] + 1])
    num_cycles = len(cycles)

    state_count = []
    for cycle in cycles:
        # Determine the number of times each cycle visits each state
        state_count.append(([len(np.where(cycle == state)[0]) for state in x_values]))
    state_count = np.transpose(np.clip(state_count, 0, 5))

    su = []
    for cycle in range(6):
        su.append([(sct == cycle).sum() for sct in state_count])
    su = np.transpose(su)

    piks = ([([get_pik_value(uu, state) for uu in range(6)]) for state in x_values])
    inner_term = num_cycles * np.array(piks)
    chi = np.sum(1.0 * (np.array(su) - inner_term) ** 2 / inner_term, axis=1)
    p_values = ([spc.gammaincc(2.5, cs / 2.0) for cs in chi])
    return 0.000000024549235245








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


spec = [('x', float32), ('y', float32)]


@jitclass(spec)
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


@jit
def is_in_list(array, point):
    for num in range(len(array)):
        if point.x == array[num].x and point.y == array[num].y:
            return True
    return False


@jit
def is_good_to_park(point1, point2):
    return abs(point1.x - point2.x) > 1 or abs(point1.y - point2.y) > 1

@jit
def parking_lot(array):
    x = array[randint(0, len(array)-1)]
    y = array[randint(0, len(array)-1)]
    parked = []
    parked.append(Point(x, y))

    for i in range(1, 12000):
        flag = True
        xi = array[randint(0, len(array)-1)]
        yi = array[randint(0, len(array)-1)]
        p = Point(xi, yi)
        for j in range(len(parked)):
            if not is_good_to_park(p, parked[j]):
                flag = False
                break
        if flag:
            parked.append(p)
    return len(parked)


def ovеrlapping_test(array):
    UNIMAX = 4294967296  # pow(2, 32)
    no_obs = 10
    no_sum = 100
    no_num = 100
    mean = .5 * no_num
    rstd = math.sqrt(12)

    y = []
    p = [0] * no_sum
    pv = [0] * no_obs

    min_el = min(array)
    max_el = max(array)
    array_norm = [(x - min_el) / (max_el + min_el) for x in array]

    x = [0] * len(array)

    for I in range(1, no_obs + 1):
        for J in range(no_sum):

            sum_ = 0
            y = array.copy()
            sum_ = sum(array)

            for k in range(1, no_num):
                tmp = y[k - 1]
                y[k - 1] = (sum_ - mean) * rstd
                sum_ -= (tmp - y[k])

            y[no_num - 1] = (sum_ - mean) * rstd
            x[0] = y[0] / math.sqrt(no_num)

            x[1] = -x[0] * (no_num - 1) / math.sqrt(2 * no_num - 1.) + y[1] * math.sqrt(no_num / (2 * no_num - 1.))
            x[0] = ss.norm.cdf(x[0])
            x[1] = ss.norm.cdf(x[1])
            
            for k in range(2, no_num):
                a = 2 * no_num - k
                b = 2 * a - 2
                x[k] = y[0] / math.sqrt(a * b) - math.sqrt((a-1) / (b+2)) * y[k - 1] + y[k] * math.sqrt(a / b)
                x[k] = ss.norm.cdf(x[k])

            p[J] = ss.kstest(x, 'norm', args=(mean, rstd))

        pv[I - 1] = ss.kstest(p, 'norm', args=(mean, rstd))

    return ss.kstest(pv, 'norm', args=(mean, rstd))[1]


if __name__ == '__main__':
    # file_names = ['LFSR_10.bin', 'LFSR_20.bin', 'LFSR_30.bin']
    file_names = ['2-10 (лекции).doc']
    degree = 10
    for name in file_names:
        lfsr = read_bin_sequence(name)

        lfsr_parking = lfsr.copy()

        # parking lot test
        ks = []
        for i in range(10):
            res = parking_lot(lfsr_parking)
            ks.append(res)
        print(f'Результаты parking lot теста для полинома с примитивным многочленом степени {degree}')
        mu = np.mean(ks)
        sigma = np.std(ks, ddof=1)

        print(stat)
        print()

        # overlapping sums test

        print(f'Результаты overlapping теста для полинома с примитивным многочленом степени {degree}')
        print(overlapping_test(lfsr))
        print()

        degree += 10
