f = open("input.txt")
w = open("output.txt", 'w')
n_condition = int(f.readline())
d = [0] * n_condition
for line in f:
    a, b = [int(j) for j in line.split()]
    d[b - 1] = a
for i in range(n_condition):
    w.write(str(d[i]) + ' ')
