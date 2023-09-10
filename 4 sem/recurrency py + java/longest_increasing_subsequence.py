def LongestIncreasingSubsequenceLength(current_subsequence, size):
    check_list = [0] * (size + 1)
    check_list[0] = current_subsequence[0]
    length = 1
    for i in range(1, size):
        if current_subsequence[i] < check_list[0]:
            check_list[0] = current_subsequence[i]
        elif current_subsequence[i] > check_list[length - 1]:
            check_list[length] = current_subsequence[i]
            length += 1
        else:
            # like q-sort algo
            z = -1
            l = 0
            r = length
            while l < r:
                m = (l + r) // 2
                if current_subsequence[i] == check_list[m] or (
                        check_list[m] > current_subsequence[i] > check_list[m - 1]):
                    z = m
                    break
                if current_subsequence[i] < check_list[m]:
                    r = m
                else:
                    l = m + 1
            check_list[z] = current_subsequence[i]
    return length


f = open('input.txt')
n = int(f.readline())
line = f.readline()
subsequence = [int(i) for i in line.split()]
open('output.txt', 'w').write(str(LongestIncreasingSubsequenceLength(subsequence, n)))

# 1. If A[i] is smallest among all end
#    candidates of active lists, we will start
#    new active list of length 1.
# 2. If A[i] is largest among all end candidates of
#   active lists, we will clone the largest active
#   list, and extend it by A[i].
#
# 3. If A[i] is in between, we will find a list with
#   largest end element that is smaller than A[i].
#   Clone and extend this list by A[i]. We will discard all
#   other lists of same length as that of this modified list.
