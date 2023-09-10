f = open("input.txt")
w = open("output.txt", 'w')
n_condition = int(f.readline())
d = [0] * n_condition
for i in range(n_condition):
    line = f.readline().split()
    a_string = [int(line[k]) for k in range(n_condition)]
    for j in range(n_condition):
        if a_string[j] == 1:
            d[j] = i + 1
for i in range(n_condition):
    w.write(str(d[i]) + ' ')
