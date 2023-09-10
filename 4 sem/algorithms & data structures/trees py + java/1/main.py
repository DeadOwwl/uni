f = open('input.txt')
w = open('output.txt', 'w')
s = set()
for line in f:
    s.add(int(line))
sum = 0
for element in s:
    sum += element
w.write(str(sum))
