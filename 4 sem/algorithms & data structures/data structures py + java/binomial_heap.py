n = int(open("input.txt").readline())
w = open("output.txt", 'w')
lst = reversed(format(n, 'b'))
lst = enumerate(lst)
flag = False
for i, c in lst:
    if c == '1':
        flag = True
        w.write(str(i) + '\n')
if flag is False:
    w.write(str(-1))
