def binary_search(array, element):
    ans = []
    left = 0
    right = len(array)
    while left < right:
        k = (left + right) // 2
        if element == array[k]:
            ans.append(1)
            break
        elif element < array[k]:
            right = k
        else:
            left = k + 1
    if len(ans) == 0:
        ans.append(0)

    left = 0
    right = len(array)
    while left < right:
        k = (left + right) // 2
        if element <= array[k]:
            right = k
        else:
            left = k + 1
    ans.append(left)

    left = 0
    right = len(array)
    while left < right:
        k = (left + right) // 2
        if element < array[k]:
            right = k
        else:
            left = k + 1
    ans.append(left)

    return ans


n_condition = int(input())
line = input().split()
array_condition = [int(i) for i in line]
k_condition = int(input())
line = input().split()
requests_condition = [int(i) for i in line]
answer = []
for i in range(k_condition):
    answer = binary_search(array_condition, requests_condition[i])
    print(str(answer[0]), end=' ')
    print(str(answer[1]), end=' ')
    print(str(answer[2]))
