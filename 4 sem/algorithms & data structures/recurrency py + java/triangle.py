def wtf(n, matrix):
    result = [[0] * n for _ in range(n)]
    for i in range(n - 1, -1, -1):
        for j in range(0, i + 1, 1):
            if i == n - 1:
                result[i - j][j] = matrix[i - j][j]
            else:
                result[i - j][j] = max(result[i - j + 1][j] + matrix[i - j][j],
                                       result[i - j][j + 1] + matrix[i - j][j])
    return result[0][0]


if __name__ == '__main__':
    f = open("input.txt")
    n_condition = int(f.readline())
    matrix_condition = [[0] * n_condition for i in range(n_condition)]
    for i in range(n_condition):
        line = f.readline().split()
        for k in range(len(line)):
            matrix_condition[i - k][k] = int(line[k])

    open("output.txt", 'w').write(str(wtf(n_condition, matrix_condition)))
