def files_num(k, n):
    possible = [k, k * k]
    for i in range(2, n):
        possible.append(possible[i - 1] * k + possible[i - 2] * k)
    return sum(i for i in possible)


line = open("input.txt").readline()
k_condition, n_condition = [int(i) for i in line.split()]
open("output.txt", 'w').write(str(files_num(k_condition, n_condition)))
