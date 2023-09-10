def is_binary_heap(array):
    answer = "Yes"
    for i in range(len(array) // 2):
        if (array[i] > array[i * 2 + 1]) or (2 * (i + 1) < len(array) and array[i] > array[2 * (i + 1)]):
            answer = "No"
            break
    return answer


f = open("input.txt")
n_condition = int(f.readline())
array_condition = [int(i) for i in f.readline().split()]
# array_condition.insert(0, 0)
open("output.txt", 'w').write(is_binary_heap(array_condition))