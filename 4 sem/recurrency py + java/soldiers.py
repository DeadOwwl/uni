def methods_num(n):
    if n <= 3:
        return 1
    if n & 1 == 0:
        return 2 * methods_num(n // 2)
    else:
        return methods_num(n // 2) + methods_num(n // 2 + 1)


n_condition = int(open("input.txt").readline())
open("output.txt", 'w').write(str(methods_num(n_condition)))