from sortedcontainers import SortedList


def main_process():
    q = SortedList()
    i = 0
    s_for_moment = 0
    s_for_element = 0
    ans = []
    while i < n:
        # adding
        while len(q) != sequence_in_moment[s_for_moment]:
            q.add(sequence_elements[s_for_element])
            s_for_element += 1
        s_for_moment += 1
        # getting
        ans.append(q[i])
        i += 1
    return ans


f = open("input.txt", "r", encoding="utf-8-sig")
w = open("output.txt", 'w')
main_queue = []
line = f.readline().split()
m, n = [int(i) for i in line]
sequence_elements = []
line = f.readline().split()
for i in line:
    sequence_elements.append(int(i))
sequence_in_moment = []
line = f.readline().split()
for i in line:
    sequence_in_moment.append(int(i))
answer = main_process()
for i in range(len(answer)):
    if i == len(answer) - 1:
        w.write(str(answer[i]))
    else:
        w.write(str(answer[i]) + ' ')