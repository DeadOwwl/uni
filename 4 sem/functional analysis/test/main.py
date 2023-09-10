I = map()
e = 10**(-3)


def new_f(matrix_a, matrix_x):
    matrix_f = [[]]
    for i in range(4):
        matrix_f[0][i] = 0
        for j in range(4):
            matrix_f[0][j] = matrix_f[0][i] + matrix_a[i][j] * matrix_x[0][j]
    return matrix_f


def first_norm(matrix_a):
    maximum = 0
    for j in range(4):
        norma = 0
        for i in range(4):
            norma += abs(matrix_a[i][j])
        maximum = max(maximum, norma)
    return maximum


def e_testing(matrix_x):
    summary = 0
    for i in range(4):
        summary += summary + matrix_x[0][i] * matrix_x[0][i]
    return summary**(1 / 2)


def matrix_multiplication(matrix_a, matrix_b):
    matrix_c = [[]]
    for i in range(4):
        for j in range(4):
            matrix_c[i][j] = 0
            for k in range(4):
                matrix_c[i][j] = matrix_c[i][j] + matrix_a[i][k] * matrix_b[k][j]
    return matrix_c


def matrix_tranposing(matrix_a):
    matrix_b = [[]]
    for i in range(4):
        for j in range(4):
            matrix_b[i][j] = matrix_a[j][i]
    return matrix_b


a = [[1, -5, 1, 2], [-16, -3, 5, -4], [-1, 20, 12, 0], [2, -1, 3, -10]]
f = [[32, -74, 0, -6]]
at = matrix_tranposing(a)
x = [[]]
aa = matrix_multiplication(at, a)
ff = new_f(at, f)
n = first_norm(aa)
b = []
for i in range(4):
    for j in range(4):
        if i == j:
            b[i][j] = 1 - aa[i][j] / n
        else:
            b[i][j] = -aa[i][j] / n
g = []
for i in range(4):
    for j in range(4):
        g[i][j] = ff[i][j] / n
counter = 0
x_it = g
eps = 0
while True:
    temp = new_f(b, x_it)
    counter += 1
    tmp = [temp[0][0], temp[0][1], temp[0][2], temp[0][3]]
    for i in range(1):
        for j in range(4):
            temp[i][j] = temp[i][j] = x_it[i][j]
    x_it = tmp
    eps = e_testing(temp)
    if eps <= e:
        break
x = x_it
print("Количество итераций: " + str(counter))
print("Коэффицент сжатия: " + str(eps))
print("Полученные корни: "+ x_it)
